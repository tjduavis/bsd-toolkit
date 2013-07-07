/*
 * $Id: HeadTagTest.java 471756 2006-11-06 15:01:43Z husted $
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
package org.apache.struts2.views.jsp.ui;

import org.apache.struts2.components.Head;
import org.apache.struts2.views.jsp.AbstractUITagTest;

/**
 * Unit test for {@link HeadTag}.
 * <p/>
 * Note: If unit test fails with encoding difference check the src/test/struts.properties
 * and adjust the .txt files accordingly
 *
 */
public class HeadTagTest extends AbstractUITagTest {

    private HeadTag tag;

    public void testHead1() throws Exception {
        tag.doStartTag();
        tag.doEndTag();

        verify(HeadTagTest.class.getResource("HeadTagTest-1.txt"));
    }

    public void testHead1NoCalender() throws Exception {
        tag.doStartTag();
        tag.doEndTag();
        tag.setCalendarcss(null); // null = should use calendar-blue.css

        verify(HeadTagTest.class.getResource("HeadTagTest-1.txt"));
    }

    public void testHead2() throws Exception {
        tag.setTheme("ajax");
        tag.doStartTag();
        Head component = (Head) tag.getComponent();
        assertTrue(!component.isDebug());
        tag.doEndTag();

        verify(HeadTagTest.class.getResource("HeadTagTest-2.txt"));
        assertTrue("should have debug false", writer.toString().indexOf("isDebug: false") > -1);
    }

    public void testHead3() throws Exception {
        tag.setTheme("ajax");
        tag.setDebug("true");
        tag.doStartTag();
        Head component = (Head) tag.getComponent(); // must be done between start and end
        assertTrue(component.isDebug());
        tag.doEndTag();

        verify(HeadTagTest.class.getResource("HeadTagTest-3.txt"));
        assertTrue("should have debug true", writer.toString().indexOf("isDebug: true") > -1);
    }

    public void testHead4() throws Exception {
        tag.setCalendarcss("my-calendar");
        tag.doStartTag();
        tag.doEndTag();

        verify(HeadTagTest.class.getResource("HeadTagTest-4.txt"));
        assertEquals("my-calendar", tag.getCalendarcss());
    }

    public void testHead4b() throws Exception {
        tag.setCalendarcss("my-calendar.css");
        tag.doStartTag();
        Head component = (Head) tag.getComponent(); // must be done between start and end
        assertEquals("my-calendar.css", component.getCalendarcss());
        tag.doEndTag();

        verify(HeadTagTest.class.getResource("HeadTagTest-4.txt"));
        assertEquals("my-calendar.css", tag.getCalendarcss());
    }

    protected void setUp() throws Exception {
        super.setUp();
        tag = new HeadTag();
        tag.setPageContext(pageContext);
    }

    protected void tearDown() throws Exception {
        super.tearDown();
    }

}
