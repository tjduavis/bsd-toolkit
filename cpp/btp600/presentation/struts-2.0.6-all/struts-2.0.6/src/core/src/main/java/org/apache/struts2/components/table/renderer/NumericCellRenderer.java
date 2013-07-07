/*
 * $Id: NumericCellRenderer.java 471756 2006-11-06 15:01:43Z husted $
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
package org.apache.struts2.components.table.renderer;

import java.text.DecimalFormat;

import org.apache.struts2.components.table.WebTable;


/**
 */
public class NumericCellRenderer extends AbstractCellRenderer {

    DecimalFormat _formater = new DecimalFormat();

    /**
     * this is the format string that DecimalFormat would use.
     *
     * @see DecimalFormat
     */
    String _formatString = null;

    /**
     * if set the is the color to use if Number is negative.
     */
    String _negativeColor = null;

    /**
     * if set this is the color to render if number is positive
     */
    String _positiveColor = null;


    public NumericCellRenderer() {
        super();
    }


    public String getCellValue(WebTable table, Object data, int row, int col) {
        StringBuffer retVal = new StringBuffer(128);

        if (data == null) {
            return "";
        }

        if (data instanceof Number) {
            double cellValue = ((Number) data).doubleValue();

            if (cellValue >= 0) {
                processNumber(retVal, _positiveColor, cellValue);
            } else {
                processNumber(retVal, _negativeColor, cellValue);
            }

            return retVal.toString();
        }

        return data.toString();
    }

    public void setFormatString(String format) {
        _formatString = format;
        _formater.applyPattern(_formatString);
    }

    public void setNegativeColor(String color) {
        _negativeColor = color;
    }

    public void setPositiveColor(String color) {
        _positiveColor = color;
    }

    protected void processNumber(StringBuffer buf, String color, double cellValue) {
        if (color != null) {
            buf.append(" <font color='").append(color).append("'>");
        }

        buf.append(_formater.format(cellValue));

        if (color != null) {
            buf.append("</font>");
        }
    }
}
