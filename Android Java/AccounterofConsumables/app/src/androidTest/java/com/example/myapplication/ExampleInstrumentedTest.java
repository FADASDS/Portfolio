package com.example.myapplication;

import androidx.test.core.app.ActivityScenario;
import androidx.test.espresso.action.ViewActions;
import androidx.test.ext.junit.rules.ActivityScenarioRule;
import androidx.test.espresso.Espresso;
import androidx.test.espresso.matcher.ViewMatchers;
import androidx.test.ext.junit.runners.AndroidJUnit4;
import androidx.test.filters.LargeTest;
import androidx.test.platform.app.InstrumentationRegistry;


import org.hamcrest.Matchers;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import static androidx.test.espresso.Espresso.onData;
import static androidx.test.espresso.action.ViewActions.click;
import static androidx.test.espresso.action.ViewActions.typeText;
import static androidx.test.espresso.assertion.ViewAssertions.matches;
import static androidx.test.espresso.matcher.ViewMatchers.isAssignableFrom;
import static androidx.test.espresso.matcher.ViewMatchers.isClickable;
import static androidx.test.espresso.matcher.ViewMatchers.isDisplayed;
import static androidx.test.espresso.matcher.ViewMatchers.isEnabled;
import static androidx.test.espresso.matcher.ViewMatchers.withId;
import static androidx.test.espresso.matcher.ViewMatchers.withText;

import static org.hamcrest.CoreMatchers.anything;
import static org.hamcrest.CoreMatchers.instanceOf;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.Matchers.allOf;
import static org.junit.Assert.assertEquals;

import android.app.Activity;
import android.content.Context;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.DatePicker;

/**
 * Instrumented test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)

public class ExampleInstrumentedTest {
    @Rule
    public ActivityScenarioRule<MainActivity> activityRule = new ActivityScenarioRule<>(MainActivity.class);
    @Test
    public void T_001_Try_openNoteCreator() {

        Espresso.onView(ViewMatchers.withId(R.id.openNoteCreator))
                .perform(click());
    }
    @Test
    public void T_002_Try_pressCancel() {

        Espresso.onView(ViewMatchers.withId(R.id.openNoteCreator))
                .perform(click());
        Espresso.onView(withId(R.id.buttonCancel)).check(matches(isClickable())).perform(click());
    }
    @Test
    public void T_003_Try_pressCreate() {

        Espresso.onView(ViewMatchers.withId(R.id.openNoteCreator))
                .perform(click());
        Espresso.onView(withId(R.id.buttonCreate)).check(matches(isEnabled()))
                .perform(click());
    }
    @Test
    public void T_004_Try_pressCreate_filled_fields() {

        String manufacture = "colgate";
        String model = "Ks142";
        String startDate = "13/03/2023";
        String endDate = "13/05/2023";

        Espresso.onView(ViewMatchers.withId(R.id.openNoteCreator))
                .perform(click());

        Espresso.onView(withId(R.id.editTextManufacturer))
                .perform(typeText(manufacture));

        Espresso.onView(withId(R.id.editTextModel))
                .perform(typeText(model));

        Espresso.onView(withId(R.id.editStartData))
                .perform(typeText(startDate));

        Espresso.onView(withId(android.R.id.button1)).perform(click());

        Espresso.onView(withId(R.id.editEndData))
                .perform(typeText(endDate));

        Espresso.onView(withId(android.R.id.button1)).perform(click());

        Espresso.onView(withId(R.id.buttonCreate)).check(matches(isEnabled()));
    }
    @Test
    public void T_005_Try_pressCreate_wrong_data() {

        String manufacture = "colgate";
        String model = "Ks142";
        String startDate = "13/05/2023";
        String endDate = "13/03/2023";

        Espresso.onView(ViewMatchers.withId(R.id.openNoteCreator))
                .perform(click());

        Espresso.onView(withId(R.id.editTextManufacturer))
                .perform(typeText(manufacture));

        Espresso.onView(withId(R.id.editTextModel))
                .perform(typeText(model));

        Espresso.onView(withId(R.id.editStartData))
                .perform(typeText(startDate));

        Espresso.onView(withId(android.R.id.button1)).perform(click());

        Espresso.onView(withId(R.id.editEndData))
                .perform(typeText(endDate));

        Espresso.onView(withId(android.R.id.button1)).perform(click());

        Espresso.onView(withId(R.id.buttonCreate)).check(matches(isEnabled()));
        try {
            Espresso.onView(withId(R.id.buttonCreate))
                    .perform(ViewActions.click());
        } catch (Exception e) {
            // Handle the exception here
            System.out.println("Exception caught: " + e.getMessage());
        }
    }
}