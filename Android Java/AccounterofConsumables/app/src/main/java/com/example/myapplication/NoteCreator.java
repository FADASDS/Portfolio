package com.example.myapplication;

import android.app.DatePickerDialog;
import android.app.Dialog;
import android.content.Context;
import android.os.Build;
import android.os.SystemClock;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import androidx.annotation.RequiresApi;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Calendar;

/**
 * Класс для создания заметок.
 */
public class NoteCreator {

    private Context context;
    private Dialog dialog;
    private Spinner spinnerType;
    private EditText editTextManufacturer;
    private EditText editTextModel;
    private EditText editStartData;
    private EditText editEndData;
    private Button buttonCreate;
    private Exception exception = new Exception();

    /**
     * Конструктор класса NoteCreator.
     *
     * @param context Контекст приложения.
     */
    public NoteCreator(Context context) {
        this.context = context;
        createNoteCreator();
    }

    private void createNoteCreator() {
        dialog = new Dialog(context);
        dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
        dialog.setContentView(R.layout.note_creator_dialog);
        dialog.setCancelable(true);

        spinnerType = dialog.findViewById(R.id.spinnerType);
        editTextManufacturer = dialog.findViewById(R.id.editTextManufacturer);
        editTextModel = dialog.findViewById(R.id.editTextModel);
        editStartData = dialog.findViewById(R.id.editStartData);
        editEndData = dialog.findViewById(R.id.editEndData);
        editTextModel = dialog.findViewById(R.id.editTextModel);
        buttonCreate = dialog.findViewById(R.id.buttonCreate);

        editStartData.setFocusable(false);
        editEndData.setFocusable(false);

        ArrayAdapter adapter = ArrayAdapter.createFromResource(context,
                R.array.consumable_types,
                R.layout.color_spinner_layout);
        adapter.setDropDownViewResource(R.layout.spinner_layout);
        spinnerType.setAdapter(adapter);
        buttonCreate.setEnabled(false); // Изначально кнопка "Создать" отключена

        buttonCreate.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.O)
            @Override
            public void onClick(View v) {
                // Обработка нажатия кнопки "Создать"
                String type = spinnerType.getSelectedItem().toString();
                String manufacturer = editTextManufacturer.getText().toString();
                String model = editTextModel.getText().toString();
                String startDate = editStartData.getText().toString();
                String endDate = editEndData.getText().toString();
                // Выполнение необходимых действий с введенными данными

                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");

                LocalDate stDate = LocalDate.parse(startDate, formatter);
                LocalDate edDate = LocalDate.parse(endDate, formatter);
                try {
                    checkData(type, model, stDate, edDate);
                } catch (Exception e) {
                    Toast.makeText(context, e.getMessage(), Toast.LENGTH_SHORT).show();
                    exception = e;

                }
                dialog.dismiss();
            }
        });

        Button buttonCancel = dialog.findViewById(R.id.buttonCancel);
        buttonCancel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Обработка нажатия кнопки "Отмена"
                dialog.dismiss();
            }
        });
        editStartData.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showDatePickerDialog(editStartData);
            }
        });
        editEndData.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showDatePickerDialog(editEndData);
            }
        });
    }

    /**
     * Отображает диалоговое окно для создания заметки.
     */
    public void showNoteCreator() {
        dialog.show();
        updateCreateButtonState();

        editTextManufacturer.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                updateCreateButtonState();
            }

            @Override
            public void afterTextChanged(Editable s) {
            }
        });
        spinnerType.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parentView, View selectedItemView, int position, long id) {
                updateCreateButtonState();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parentView) {
            }

        });
        editStartData.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                updateCreateButtonState();
            }

            @Override
            public void afterTextChanged(Editable s) {
            }
        });
        editEndData.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                updateCreateButtonState();
            }

            @Override
            public void afterTextChanged(Editable s) {
            }
        });
        editTextModel.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                updateCreateButtonState();
            }

            @Override
            public void afterTextChanged(Editable s) {
            }
        });
    }

    private void updateCreateButtonState() {
        boolean enableButton = !editStartData.getText().toString().isEmpty()
                && !editEndData.getText().toString().isEmpty();
        //&& !spinnerType.getSelectedItem().toString().isEmpty();

        buttonCreate.setEnabled(enableButton);
    }

    /**
     * Проверяет введенные данные на корректность.
     *
     * @param typeOfConsumable Тип расходного материала.
     * @param nameOfConsumable Наименование расходного материала.
     * @param startData        Дата начала использования.
     * @param endData          Дата окончания использования.
     * @return true, если данные корректны, в противном случае выбрасывается исключение.
     * @throws Exception Если данные некорректны.
     */
    public static boolean checkData(String typeOfConsumable, String nameOfConsumable, LocalDate
            startData, LocalDate endData) throws Exception {

        if (typeOfConsumable == null || typeOfConsumable.length() == 0) {
            throw new Exception(ExceptionStrings.emptyTypeOfConsumable);
        }
        if (nameOfConsumable == null || nameOfConsumable.length() == 0) {
            throw new Exception(ExceptionStrings.emptyNameOfConsumable);
        }
        if (startData == null) {
            throw new Exception(ExceptionStrings.emptyStartData);
        }
        if (endData == null) {
            throw new Exception(ExceptionStrings.emptyEndData);
        }
        if (endData.isBefore(startData)) {
            throw new Exception(ExceptionStrings.wrongDate);
        }

        return true;
    }

    private void showDatePickerDialog(EditText field) {
        // Получение текущей даты
        Calendar calendar = Calendar.getInstance();
        int year = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH);
        int dayOfMonth = calendar.get(Calendar.DAY_OF_MONTH);

        // Создание DatePickerDialog и установка выбранной даты в поле EditText
        DatePickerDialog datePickerDialog = new DatePickerDialog(context,
                new DatePickerDialog.OnDateSetListener() {
                    @Override
                    public void onDateSet(android.widget.DatePicker view, int year, int month, int dayOfMonth) {
                        String selectedDate = dayOfMonth + "/" + (month + 1) + "/" + year;
                        field.setText(selectedDate);
                    }
                }, year, month, dayOfMonth);

        // Показать DatePickerDialog
        datePickerDialog.show();
    }

}
