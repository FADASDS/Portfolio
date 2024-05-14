using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;
using System.ComponentModel;
using System.IO;
using System.Windows.Threading;
using System.Data.Common;

namespace CopyFolder
{

    public partial class MainWindow : Window
    {
        private BackgroundWorker backWorker;
        private FolderBrowserDialog hFolderDialog;
        private string sourceFolder;
        private string targetFolder;
        private int step;
        private long directory_size;
        public MainWindow()
        {
            InitializeComponent();
            backWorker = new BackgroundWorker();
            InitWorker();
            hFolderDialog = new FolderBrowserDialog();
            sourceFolder = "";
            targetFolder = "";
            step = 10;
            directory_size = 0;
        }

        private void InitWorker() {


            backWorker.WorkerReportsProgress = true;
            backWorker.WorkerSupportsCancellation = true;
            backWorker.ProgressChanged += BackgroundWorker_ProgressChanged;
            backWorker.DoWork += StartCopyingProcess;
            backWorker.RunWorkerCompleted += BackgroundWorker_RunWorkerCompleted;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Controls.Button clickedButton = (System.Windows.Controls.Button)sender;
            hFolderDialog.ShowDialog();
            string selectedPath = hFolderDialog.SelectedPath;

            if (clickedButton.Name == "btnChooseFolder1") {

                txtBoxSourceFolder.Text = selectedPath;
                btnStart.IsEnabled = true;
            }
            else {

                txtBoxTargetFolder.Text = selectedPath;

            }
        }

        private void btnStop_Click(object sender, RoutedEventArgs e)
        {
            btnStop.IsEnabled = !(btnStart.IsEnabled = btnChooseFolder1.IsEnabled =
                     btnChooseFolder2.IsEnabled = true);
            backWorker.CancelAsync();
        }

        private void btnStart_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                btnStart.IsEnabled = btnChooseFolder1.IsEnabled =
                btnChooseFolder2.IsEnabled = !(btnStop.IsEnabled = true);
                directory_size = (Directory.EnumerateFiles(txtBoxSourceFolder.Text, 
                    "*", SearchOption.AllDirectories).
                    Sum(fileInfo => new FileInfo(fileInfo).Length));
                progressBarGeneral.Maximum = directory_size;
                sourceFolder = txtBoxSourceFolder.Text;
                targetFolder = txtBoxTargetFolder.Text;
                backWorker.RunWorkerAsync();
            }
            catch (Exception exc)
            {
                System.Windows.MessageBox.Show("Было вызвано исключение.\n\nСообщение: " + exc.Message);
            }
            


        }
        private void StartCopyingProcess(object? sender, DoWorkEventArgs e)
        {
            try
            {
                    CopyDirectory(sourceFolder, targetFolder);
              
            }
            catch (Exception exception)
            {
                System.Windows.MessageBox.Show("Было вызвано исключение.\n\nСообщение: " + exception.Message);
            }
        }

        private void CopyDirectory(string source_path, string destination_path)
        {

            Directory.CreateDirectory(destination_path); // Создаем директорию назначения (если ее нет) 

            foreach (string file in Directory.GetFiles(source_path)) // Берем имя каждого файла исходной директории по очереди
            {
                if (backWorker.CancellationPending)
                    return; // Пришло сообщение об отмене задачи, выходим из функции

                var source_filename = System.IO.Path.GetFileName(file); // Обрезаем абсолютный путь, получаем имя файла
                var destination_filename = System.IO.Path.Combine(destination_path, source_filename); // Подготавливаем полный путь для записи файла и имя его

                var bytes_were_written = CopyFile(file, destination_filename); // Копируем файл
                backWorker.ReportProgress(bytes_were_written, 1);

            }

            var directoryInfo = new DirectoryInfo(source_path); // Получим информацию о нашей текущей директории
            foreach (var subDirectory in directoryInfo.GetDirectories()) // Для каждой подпапки выполним копирование ее файлов
            {
                CopyDirectory(subDirectory.FullName, System.IO.Path.Combine(destination_path, subDirectory.Name));
            }
        }

        private int CopyFile(string source_path, string destination_path)
        {

            var source_file = new FileStream(source_path, FileMode.Open, FileAccess.Read); // Открываем исходный файл для чтения
            var destination_file = new FileStream(destination_path, FileMode.Create); // Создаем новый файл в запись
            int dec = 0;
            int bytes_were_read = 0;
            int bytes_were_written = 0;
            byte[] buffer = new byte[2048];

            while ((bytes_were_read = source_file.Read(buffer, 0, buffer.Length)) > 0)
            {

                if (backWorker.CancellationPending)
                    break;

                destination_file.Write(buffer, 0, bytes_were_read);

                bytes_were_written += bytes_were_read;

                if (bytes_were_written / step > dec)
                {
                    int.TryParse((100 * source_file.Position / source_file.Length).ToString(), out var progress_in_percent);
                    backWorker.ReportProgress(progress_in_percent);
                    dec++;
                }


            }

            source_file.Close();
            destination_file.Close();

            if (backWorker.CancellationPending)
            {
                File.Delete(destination_path);
                return 0;
            }
            return bytes_were_written;
        }

        private void BackgroundWorker_ProgressChanged(object? sender, ProgressChangedEventArgs e)
        {

            if (e.UserState == null)
            {

                
                progressBarLocal.Value = e.ProgressPercentage;

            }
            else
            {
                progressBarGeneral.Value += e.ProgressPercentage;
            }

        }
        private void BackgroundWorker_RunWorkerCompleted(object? sender, RunWorkerCompletedEventArgs e) {

            btnStop.IsEnabled = !(btnStart.IsEnabled = btnChooseFolder1.IsEnabled =
                    btnChooseFolder2.IsEnabled = true);

        }
    }
}
