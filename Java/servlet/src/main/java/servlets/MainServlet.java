package servlets;

import java.io.*;
import java.nio.file.Path;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.nio.file.Files;
import javax.servlet.http.Part;
import java.io.IOException;
import javax.servlet.annotation.*;
import java.util.ArrayList;

@WebServlet(urlPatterns = {"/serv"})
@MultipartConfig(location = "C:\\Users\\User\\IdeaProjects\\servlet")
public class MainServlet extends HttpServlet {

    String filename;
    boolean flag = false;
    PrintWriter out;
    @Override
    public void init(ServletConfig config) throws ServletException {
        super.init(config);
        filename="";
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {


        out = resp.getWriter();
        out.println("<html><body>");
        out.print("<form action=\"");
        out.print("serv\" ");
        out.println("method=POST enctype=multipart/form-data>");
        out.println("<input type=file name=fname>");
        out.println("<br>");
        out.println("<input type=submit>");
        out.println("<br>");
        if(flag==true)
            out.println("Successful!");
        out.println("</form>");
        out.println("</body></html>");
        flag = false;

    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        for (Part part : req.getParts()) {
            if (part.getName().equals("fname")) {
                filename = part.getSubmittedFileName();
                part.write(part.getSubmittedFileName());
            }
        }
        resp.sendRedirect("/serv");
        formateFile();
        }
 String makeStringfromfile(String filename)throws IOException{

     String infile ="";
     if(!filename.equals(""))
     {
         String path = "C:\\Users\\User\\IdeaProjects\\servlet\\" + filename;
         infile = Files.readString(Path.of(path));
         String workstring = infile.substring(1);
         return workstring;
     }
     else return "Error";


 }
    void formateFile() throws IOException {

        ArrayList<String> slist = new ArrayList<>();
        String workstring = makeStringfromfile(filename);
        if(!workstring.equals("Error")){
            String[] headarray = workstring.split("\t");

            for(int i=0; i < headarray.length;i++)
            {
                slist.addAll(formateParagraph(headarray[i], 80));
            }
            createFile(slist);
            flag = true;
        }

    }

    ArrayList<String> formateParagraph(String paragraph, int num_symb){

        ArrayList<String> slist = new ArrayList<>();
        String timestring = "";
        String buff = "";
        int head_length = 0;
        int num_string = 0;
        int right_border=0;
        int left_border = 0;
        head_length = paragraph.length();
        num_string = head_length/num_symb;
        timestring+="   ";
        for(int j = 0; j< num_string;j++){
            right_border+=num_symb;
            if(paragraph.charAt(left_border)==' '&&paragraph.charAt(left_border+1)!=' ')
            {
                left_border++;
                right_border++;
            }
            timestring += paragraph.substring(left_border,right_border);
            if(timestring.charAt(timestring.length()-1)==' ')
            {
                buff = timestring.trim()+paragraph.substring(right_border,right_border+1);
                timestring=buff;
            }
            left_border = right_border;
            slist.add(timestring);
            timestring="";
        }
        if(head_length-right_border>0)
        {
            timestring=paragraph.substring(right_border);
            buff = timestring.trim();
            timestring=buff;
            slist.add(timestring);
            timestring="";
        }
        return slist;
    }
void createFile(ArrayList<String> slist) throws IOException {

    try{
        String path = "C:\\Users\\User\\Desktop\\" +"formatted_"+ filename;
        Files.createFile(Path.of(path));
        FileWriter writer = new FileWriter(path);
        for(int i =0;i< slist.size();i++)
        {
            writer.write(slist.get(i)+"\n");
        }
        writer.close();

    }
    catch(IOException e){
    }


}
}
