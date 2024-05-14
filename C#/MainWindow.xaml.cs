using System;
using System.Data;
using System.Windows;
using MySql.Data.MySqlClient;


namespace Interface
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private MySqlConnection connection;
        private MySqlCommand cmd;
        private DataTable DataTable;
        private string tableClients = "clients";
        private string tableTravels = "travel";
        public MainWindow()
        {
            InitializeComponent();
            ConnectDB();

        }

        private void ConnectDB(){

            string connectionString = "Server=localhost;" +
                "Database=mydb;" +
                "User ID=root;Password=root;";
            
            connection = new MySqlConnection(connectionString);
            connection.Open();
            DataGridClients.ItemsSource = LoadTable("SELECT * FROM " + tableClients).DefaultView;
            DataGridTravels.ItemsSource = LoadTable("SELECT * FROM " + tableTravels).DefaultView;

            connection.Close();        

        }
        private DataTable LoadTable(string query) {

            cmd = new MySqlCommand(query, connection);
            DataTable = new DataTable();
            DataTable.Load(cmd.ExecuteReader());
            return DataTable;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            DataRowView selectedClient = (DataRowView)DataGridClients.SelectedItem;

            if (selectedClient != null)
            {

                connection.Open();
                cmd = new MySqlCommand("INSERT INTO " + tableClients +
                   " (ФИО, Паспорт, Пол, Возраст, Категория) VALUES (@FIO, @Passport, @Sex, @Age, @Category)",
                   connection);
                cmd.Parameters.AddWithValue("@FIO", selectedClient["ФИО"]);
                cmd.Parameters.AddWithValue("@Passport", selectedClient["Паспорт"]);
                cmd.Parameters.AddWithValue("@Sex", selectedClient["Пол"]);
                cmd.Parameters.AddWithValue("@Age", selectedClient["Возраст"]);
                cmd.Parameters.AddWithValue("@Category", selectedClient["Категория"]);
                cmd.ExecuteNonQuery();
                DataGridClients.ItemsSource = LoadTable("SELECT * FROM " + tableClients).DefaultView;

                connection.Close();
            }
        }

        private void btnAddTravel_Click(object sender, RoutedEventArgs e)
        {
            DataRowView selectedTravel = (DataRowView)DataGridTravels.SelectedItem;

            if (selectedTravel != null) {

                connection.Open();
           
                cmd = new MySqlCommand("INSERT INTO " + tableTravels +
                    " (InRaceNum, OutRaceNum, Hotel) VALUES (@InRaceNum, @OutRaceNum, @Hotel)", connection);
                cmd.Parameters.AddWithValue("@InRaceNum", selectedTravel["InRaceNum"]);
                cmd.Parameters.AddWithValue("@OutRaceNum", selectedTravel["OutRaceNum"]);
                cmd.Parameters.AddWithValue("@Hotel", selectedTravel["Hotel"]);
                cmd.ExecuteNonQuery();
                DataGridTravels.ItemsSource = LoadTable("SELECT * FROM " + tableTravels).DefaultView;
                connection.Close();
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            DataRowView selectedTravel = (DataRowView)DataGridTravels.SelectedItem;

            if (selectedTravel != null)
            {
                int travelId = Convert.ToInt32(selectedTravel["IDTravel"]);

                connection.Open();
                cmd = new MySqlCommand("DELETE FROM " + tableTravels + " WHERE IDTravel = @Id", connection);
                cmd.Parameters.AddWithValue("@Id", travelId);
                cmd.ExecuteNonQuery();
                DataGridTravels.ItemsSource = LoadTable("SELECT * FROM " + tableTravels).DefaultView;

                connection.Close();
            }
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            DataRowView selectedClient = (DataRowView)DataGridClients.SelectedItem;

            if (selectedClient != null)
            {
                int clientId = Convert.ToInt32(selectedClient["IDКлиента"]);

                connection.Open();
                cmd = new MySqlCommand("DELETE FROM " + tableClients + " WHERE IDКлиента = @Id", connection);
                cmd.Parameters.AddWithValue("@Id", clientId);
                cmd.ExecuteNonQuery();
                DataGridClients.ItemsSource = LoadTable("SELECT * FROM " + tableClients).DefaultView;

                connection.Close();
            }
        }
    }
}
