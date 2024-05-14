import javax.swing.JFrame;
import javax.swing.JLabel;
import java.awt.Color;
import java.util.ArrayList;
import javax.swing.JPanel;
import java.awt.Dimension;
import java.util.Random;
import java.awt.Font;
import java.awt.event.WindowStateListener;
import java.awt.event.WindowEvent;

class Application_1
{
    class MyStructure{
        public int par;
        public int change_x;
        public int change_y;
        public int par_x;
        public int par_y;

        public MyStructure(int par, int ch_x, int ch_y, int x, int y){
            this.par=par;
            this.change_x = ch_x;
            this.change_y = ch_y;
            this.par_x = x;
            this.par_y = y;
        }
    }
    public ArrayList<JLabel> lbl_list;
    public JPanel panel;
    JFrame mainwnd;
    MyStructure strctr;

    public Application_1()
    {
        Create_labels();
        Create_window();
 
        new WorkerThread();
    }

    void Create_window()
    {
        panel = new JPanel();
        //panel.setPreferredSize(new Dimension(800, 600));
        panel.setOpaque(false);
        panel.setLayout(null);
        mainwnd = new JFrame("Window");
        mainwnd.setPreferredSize(new Dimension(800, 600));
        mainwnd.setLayout(null);
        mainwnd.add(panel);
        mainwnd.setContentPane(panel);

        mainwnd.addWindowStateListener(new WindowStateListener() {
            public void windowStateChanged(WindowEvent event) {
                boolean isMaximized = isMaximized(event.getNewState());
                boolean wasMaximized = isMaximized(event.getOldState());
    
                if (isMaximized && !wasMaximized) {

                    panel.setSize(mainwnd.getWidth(), mainwnd.getHeight());
                    strctr.par_x = panel.getWidth()/2-(lbl_list.get(0).getWidth()/2);
                    strctr.par_y = panel.getHeight()/2-(lbl_list.get(0).getHeight()/2);
                    Add_labels(strctr.par,  strctr.par_x,  strctr.par_y);
                    
                } else if (wasMaximized && !isMaximized) {
                    panel.setSize(mainwnd.getWidth(), mainwnd.getHeight());
                    strctr.par_x = panel.getWidth()/2-(lbl_list.get(0).getWidth()/2);
                    strctr.par_y = panel.getHeight()/2-(lbl_list.get(0).getHeight()/2);
                    Add_labels(strctr.par,  strctr.par_x,  strctr.par_y);
                    
                }
            }
        });
        mainwnd.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mainwnd.getContentPane().setBackground(Color.WHITE);
        mainwnd.pack();
        mainwnd.setLocationRelativeTo(null);
        mainwnd.setVisible(true);
    }
    private static boolean isMaximized(int state) {
        return (state & JFrame.MAXIMIZED_BOTH) == JFrame.MAXIMIZED_BOTH;
    }
    ArrayList<String> Randomize_string()
    {
	    ArrayList<String> slist = new ArrayList<>();
        String rnd_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
        String str = "";
        Random r = new Random();
        int str_num = r.nextInt(7) + 3;
        for(int i =0; i< str_num;i++)
        {
            int str_length = r.nextInt(10) + 1;
            for(int j = 0; j< str_length;j++)
            {
                int index = r.nextInt(rnd_str.length());
                str += rnd_str.charAt(index);
            }
            slist.add(str);
            str="";
        }
        return slist;
    }
    void Create_labels(){
        ArrayList<String> slist = Randomize_string();
        lbl_list = new ArrayList<>();
        for(int i=0; i< slist.size(); i++)
        {
            JLabel label = new JLabel(slist.get(i));
            label.setSize(300, 60);
            lbl_list.add(label);
        }
     
    }
    void Add_labels(int par,int x, int y){
        int h = 0;
        int w = 0;
        switch(par){
            case 1:
            h = 70;
            y=0;
            for(int i=0; i< lbl_list.size(); i++)
                {
                    
                    lbl_list.get(i).setLocation(x, y);
                    //lbl_list.get(i).setBounds(x, y, 300, 60);
                    lbl_list.get(i).setFont(new Font("Serif", Font.PLAIN, 44));
                    lbl_list.get(i).setHorizontalAlignment(JLabel.CENTER);
                    panel.add(lbl_list.get(i));
                    y-=h;
                }
            break;
            case 2:
            w = 300;
            x=0;
            for(int i=0; i< lbl_list.size(); i++)
                {
                    lbl_list.get(i).setLocation(x, y);
                    //lbl_list.get(i).setBounds(x, y, 300, 60);
                    lbl_list.get(i).setFont(new Font("Serif", Font.PLAIN, 44));
                    lbl_list.get(i).setHorizontalAlignment(JLabel.CENTER);
                    panel.add(lbl_list.get(i));
                    x-=w;
                }
            break;
            case 3:
            h=70;
            w=300;
            x=0;
            y=0;
            for(int i=0; i< lbl_list.size(); i++)
            {
                lbl_list.get(i).setLocation(x, y);
                //lbl_list.get(i).setBounds(x, y, 300, 60);
                lbl_list.get(i).setFont(new Font("Serif", Font.PLAIN, 44));
                lbl_list.get(i).setHorizontalAlignment(JLabel.CENTER);
                panel.add(lbl_list.get(i));
                x-=w;
                y-=h;
            }
            break;
        }
        
    }
    MyStructure choose_change(){
        strctr =  new MyStructure(0,0,0,0,0);
        Random r = new Random();
        int par = r.nextInt(3) + 1;
       // int par = 2;
        switch(par){
            case 1:
                Add_labels(par, (panel.getWidth()/2-(lbl_list.get(0).getWidth()/2)), 0);
                strctr.par =par;
                strctr.change_x = 0;
                strctr.change_y = 1;
                strctr.par_x = 300;
                strctr.par_y = 0;
                break;
                
            case 2:
                Add_labels(par, 0, (panel.getHeight()/2-(lbl_list.get(0).getHeight()/2)));
                strctr.par =par;
                strctr.change_x = 1;
                strctr.change_y = 0;
                strctr.par_x = 0;
                strctr.par_y = 270;
                break;
            case 3:
                Add_labels(par, 1, 1);
                strctr.par =par;
                strctr.change_x = 2;
                strctr.change_y = 1;
                strctr.par_x = 0;
                strctr.par_y = 0;
                break;

        }
        return strctr;
    }
    void Move_labels(int x, int y){

        for(int i=0; i< lbl_list.size(); i++)
        {
            lbl_list.get(i).setLocation((int)lbl_list.get(i).getLocation(null).getX()+x, 
            (int)lbl_list.get(i).getLocation(null).getY()+y);
            
        }
    }
    class WorkerThread extends Thread
    {
        int fps = 10;
        MyStructure strctr = choose_change();
        
        public WorkerThread()
        {
            setDaemon(true); 
            start();
        }
 
        
        public void run()
        {
            while (true)
            {
                Move_labels(strctr.change_x, strctr.change_y);

                if(lbl_list.get(lbl_list.size()-1).getX()==panel.getWidth() | lbl_list.get(lbl_list.size()-1).getY()==panel.getHeight() )
                    Add_labels(strctr.par, strctr.par_x, strctr.par_y);
                try
                {
                    sleep(fps);
                }
                catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }
}
