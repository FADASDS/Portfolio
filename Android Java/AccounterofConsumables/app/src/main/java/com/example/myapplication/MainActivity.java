package com.example.myapplication;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.google.android.material.bottomnavigation.BottomNavigationView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import com.example.myapplication.databinding.ActivityMainBinding;

/**
 * Главная активность приложения.
 */
public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;
    private NavController navController;

    /**
     * Вызывается при создании активности.
     *
     * @param savedInstanceState Сохраненное состояние активности.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        BottomNavigationView navView = findViewById(R.id.nav_view);

        AppBarConfiguration appBarConfiguration = new AppBarConfiguration.Builder(
                R.id.navigation_home, R.id.navigation_dashboard, R.id.navigation_notifications)
                .build();

        navController = Navigation.findNavController(this, R.id.nav_host_fragment_activity_main);
        NavigationUI.setupActionBarWithNavController(this, navController, appBarConfiguration);
        NavigationUI.setupWithNavController(binding.navView, navController);

        Button buttonOpenPopup = findViewById(R.id.openNoteCreator);

        buttonOpenPopup.setOnClickListener(new View.OnClickListener() {
            /**
             * Вызывается при нажатии на кнопку.
             *
             * @param v Нажатый вид.
             */
            @Override
            public void onClick(View v) {
                NoteCreator noteCreator = new NoteCreator(MainActivity.this);
                noteCreator.showNoteCreator();
            }
        });
    }
}
