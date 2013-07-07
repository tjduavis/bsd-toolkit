/*
 * $Id: Sorter.java 471756 2006-11-06 15:01:43Z husted $
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
package org.apache.struts2.util;

import java.util.Comparator;

import com.opensymphony.xwork2.util.ValueStack;
import com.opensymphony.xwork2.util.ValueStackFactory;


/**
 * Sorters. Utility sorters for use with the "sort" tag.
 *
 * @see org.apache.struts2.views.jsp.iterator.SortIteratorTag
 * @see SortIteratorFilter
 */
public class Sorter {

    public Comparator getAscending() {
        return new Comparator() {
            public int compare(Object o1, Object o2) {
                if (o1 instanceof Comparable) {
                    return ((Comparable) o1).compareTo(o2);
                } else {
                    String s1 = o1.toString();
                    String s2 = o2.toString();

                    return s1.compareTo(s2);
                }
            }
        };
    }

    public Comparator getAscending(final String anExpression) {
        return new Comparator() {
            private ValueStack stack = ValueStackFactory.getFactory().createValueStack();

            public int compare(Object o1, Object o2) {
                // Get value for first object
                stack.push(o1);

                Object v1 = stack.findValue(anExpression);
                stack.pop();

                // Get value for second object
                stack.push(o2);

                Object v2 = stack.findValue(anExpression);
                stack.pop();

                // Ensure non-null
                if (v1 == null) {
                    v1 = "";
                }

                if (v2 == null) {
                    v2 = "";
                }

                // Compare them
                if (v1 instanceof Comparable && v1.getClass().equals(v2.getClass())) {
                    return ((Comparable) v1).compareTo(v2);
                } else {
                    String s1 = v1.toString();
                    String s2 = v2.toString();

                    return s1.compareTo(s2);
                }
            }
        };
    }

    public Comparator getComparator(String anExpression, boolean ascending) {
        if (ascending) {
            return getAscending(anExpression);
        } else {
            return getDescending(anExpression);
        }
    }

    public Comparator getDescending() {
        return new Comparator() {
            public int compare(Object o1, Object o2) {
                if (o2 instanceof Comparable) {
                    return ((Comparable) o2).compareTo(o1);
                } else {
                    String s1 = o1.toString();
                    String s2 = o2.toString();

                    return s2.compareTo(s1);
                }
            }
        };
    }

    public Comparator getDescending(final String anExpression) {
        return new Comparator() {
            private ValueStack stack = ValueStackFactory.getFactory().createValueStack();

            public int compare(Object o1, Object o2) {
                // Get value for first object
                stack.push(o1);

                Object v1 = stack.findValue(anExpression);
                stack.pop();

                // Get value for second object
                stack.push(o2);

                Object v2 = stack.findValue(anExpression);
                stack.pop();

                // Ensure non-null
                if (v1 == null) {
                    v1 = "";
                }

                if (v2 == null) {
                    v2 = "";
                }

                // Compare them
                if (v2 instanceof Comparable && v1.getClass().equals(v2.getClass())) {
                    return ((Comparable) v2).compareTo(v1);
                } else {
                    String s1 = v1.toString();
                    String s2 = v2.toString();

                    return s2.compareTo(s1);
                }
            }
        };
    }
}
