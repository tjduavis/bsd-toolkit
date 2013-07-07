/*
 * $Id: RestfulActionMapper.java 471756 2006-11-06 15:01:43Z husted $
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
package org.apache.struts2.dispatcher.mapper;

import java.net.URLDecoder;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.StringTokenizer;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts2.RequestUtils;

import com.opensymphony.xwork2.config.ConfigurationManager;


/**
 * <!-- START SNIPPET: description -->
 *
 * A custom action mapper using the following format:
 * <p/>
 * <p/>
 * <ul><tt>http://HOST/ACTION_NAME/PARAM_NAME1/PARAM_VALUE1/PARAM_NAME2/PARAM_VALUE2</tt></ul>
 * <p/>
 * You can have as many parameters you'd like to use. Alternatively the URL can be shortened to the following:
 * <p/>
 * <ul><tt>http://HOST/ACTION_NAME/PARAM_VALUE1/PARAM_NAME2/PARAM_VALUE2</tt></ul>
 * <p/>
 * This is the same as:
 * <p/>
 * <ul><tt>http://HOST/ACTION_NAME/ACTION_NAME + "Id"/PARAM_VALUE1/PARAM_NAME2/PARAM_VALUE2</tt></ul>
 * <p/>
 * Suppose for example we would like to display some articles by id at using the following URL sheme:
 * <p/>
 * <ul><tt>http://HOST/article/Id</tt></ul>
 * <p/>
 * <p/>
 * Your action just needs a setArticleId() method, and requests such as /article/1, /article/2, etc will all map
 * to that URL pattern.
 *
 * <!-- END SNIPPET: description -->
 *
 */
public class RestfulActionMapper implements ActionMapper {
    protected static final Log LOG = LogFactory.getLog(RestfulActionMapper.class);

    /* (non-Javadoc)
     * @see org.apache.struts2.dispatcher.mapper.ActionMapper#getMapping(javax.servlet.http.HttpServletRequest)
     */
    public ActionMapping getMapping(HttpServletRequest request, ConfigurationManager configManager) {
        String uri = RequestUtils.getServletPath(request);

        int nextSlash = uri.indexOf('/', 1);
        if (nextSlash == -1) {
            return null;
        }

        String actionName = uri.substring(1, nextSlash);
        HashMap<String,String> parameters = new HashMap<String,String>();
        try {
            StringTokenizer st = new StringTokenizer(uri.substring(nextSlash), "/");
            boolean isNameTok = true;
            String paramName = null;
            String paramValue;

            // check if we have the first parameter name
            if ((st.countTokens() % 2) != 0) {
                isNameTok = false;
                paramName = actionName + "Id";
            }

            while (st.hasMoreTokens()) {
                if (isNameTok) {
                    paramName = URLDecoder.decode(st.nextToken(), "UTF-8");
                    isNameTok = false;
                } else {
                    paramValue = URLDecoder.decode(st.nextToken(), "UTF-8");

                    if ((paramName != null) && (paramName.length() > 0)) {
                        parameters.put(paramName, paramValue);
                    }

                    isNameTok = true;
                }
            }
        } catch (Exception e) {
            LOG.warn(e);
        }

        return new ActionMapping(actionName, "", "", parameters);
    }

    /* (non-Javadoc)
     * @see org.apache.struts2.dispatcher.mapper.ActionMapper#getUriFromActionMapping(org.apache.struts2.dispatcher.mapper.ActionMapping)
     */
    public String getUriFromActionMapping(ActionMapping mapping) {
        String base = mapping.getNamespace() + mapping.getName();
        for (Iterator iterator = mapping.getParams().entrySet().iterator(); iterator.hasNext();) {
            Map.Entry entry = (Map.Entry) iterator.next();
            String name = (String) entry.getKey();
            if (name.equals(mapping.getName() + "Id")) {
                base = base + "/" + entry.getValue();
                break;
            }
        }

        return base;
    }
}
