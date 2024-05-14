package com.example.myapplication;

import org.junit.Assert;
import org.junit.Test;

import java.time.LocalDate;

public class Tests {

    @Test
    public void T_001_NoteCreatorTest_Basic() {

       String typeOfConsumable = "type";
       String nameOfConsumable = "name";
       LocalDate startData =  LocalDate.of(2023, 05, 05);
       LocalDate  endData =  LocalDate.of(2023, 05, 05);

       boolean expectedReturnValue = true;
       boolean actualReturnValue = false;
       try{
           actualReturnValue= NoteCreator.checkData(typeOfConsumable, nameOfConsumable, startData, endData);
       }
       catch(Exception e){

        }
       Assert.assertTrue(actualReturnValue);
    }
    @Test
    public void T_002_NoteCreatorTest_EmptyType() {

        String typeOfConsumable = "";
        String nameOfConsumable = "name";
        LocalDate startData =  LocalDate.of(2023, 05, 05);
        LocalDate  endData =  LocalDate.of(2023, 05, 05);

        String  expectedExceptionMessage = ExceptionStrings.emptyTypeOfConsumable;
        Exception exception = new Exception();
        try{
            NoteCreator.checkData(typeOfConsumable, nameOfConsumable, startData, endData);
        }
        catch(Exception e){
            exception = e;
        }
        Assert.assertNotNull(exception);
        Assert.assertEquals(expectedExceptionMessage, exception.getMessage());
    }
    @Test
    public void T_003_NoteCreatorTest_EmptyName() {

        String typeOfConsumable = "type";
        String nameOfConsumable = "";
        LocalDate startData =  LocalDate.of(2023, 05, 05);
        LocalDate  endData =  LocalDate.of(2023, 05, 05);

        String  expectedExceptionMessage = ExceptionStrings.emptyNameOfConsumable;
        Exception exception = new Exception();
        try{
            NoteCreator.checkData(typeOfConsumable, nameOfConsumable, startData, endData);
        }
        catch(Exception e){
            exception = e;
        }
        Assert.assertNotNull(exception);
        Assert.assertEquals(expectedExceptionMessage, exception.getMessage());
    }
    @Test
    public void T_004_NoteCreatorTest_wrongDate() {

        String typeOfConsumable = "type";
        String nameOfConsumable = "name";
        LocalDate startData =  LocalDate.of(2023, 05, 05);
        LocalDate  endData =  LocalDate.of(2023, 04, 05);


        String  expectedExceptionMessage = ExceptionStrings.wrongDate;
        Exception exception = new Exception();

        try{
            NoteCreator.checkData(typeOfConsumable, nameOfConsumable, startData, endData);
        }
        catch(Exception e){
            exception = e;
            System.out.println(e.getMessage());
        }
        Assert.assertNotNull(exception);
        Assert.assertEquals(expectedExceptionMessage, exception.getMessage());
    }
    @Test
    public void T_005_NoteCreatorTest_EmptyStartData() {

        String typeOfConsumable = "type";
        String nameOfConsumable = "name";
        LocalDate startData =  null;
        LocalDate  endData =  LocalDate.of(2023, 05, 05);

        String  expectedExceptionMessage = ExceptionStrings.emptyStartData;
        Exception exception = new Exception();

        try{
            NoteCreator.checkData(typeOfConsumable, nameOfConsumable, startData, endData);
        }
        catch(Exception e){
            exception = e;
        }
        Assert.assertNotNull(exception);
        Assert.assertEquals(expectedExceptionMessage, exception.getMessage());
    }
    @Test
    public void T_006_NoteCreatorTest_EmptyEndData() {

        String typeOfConsumable = "type";
        String nameOfConsumable = "name";
        LocalDate startData =  LocalDate.of(2023, 05, 05);
        LocalDate endData =  null;

        String  expectedExceptionMessage = ExceptionStrings.emptyEndData;
        Exception exception = new Exception();

        try{
            NoteCreator.checkData(typeOfConsumable, nameOfConsumable, startData, endData);
        }
        catch(Exception e){
            exception = e;
        }
        Assert.assertNotNull(exception);
        Assert.assertEquals(expectedExceptionMessage, exception.getMessage());
    }
}