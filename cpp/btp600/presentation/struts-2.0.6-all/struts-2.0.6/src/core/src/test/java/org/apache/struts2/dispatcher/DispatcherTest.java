/*
 * $Id: DispatcherTest.java 476696 2006-11-19 03:56:18Z tmjee $
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
package org.apache.struts2.dispatcher;

import java.util.HashMap;
import java.util.Locale;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts2.StrutsConstants;
import org.apache.struts2.StrutsTestCase;
import org.springframework.mock.web.MockHttpServletRequest;
import org.springframework.mock.web.MockHttpServletResponse;
import org.springframework.mock.web.MockServletContext;

import com.opensymphony.xwork2.config.ConfigurationManager;
import com.opensymphony.xwork2.util.LocalizedTextUtil;

/**
 * Test case for Dispatcher.
 *
 */
public class DispatcherTest extends StrutsTestCase {

    public void testDefaultResurceBundlePropertyLoaded() throws Exception {
        Locale.setDefault(Locale.US); // force to US locale as we also have _de and _da properties

        // some i18n messages from xwork-messages.properties
        assertEquals(
                LocalizedTextUtil.findDefaultText("xwork.error.action.execution", Locale.US),
                "Error during Action invocation");

        // some i18n messages from struts-messages.properties
        assertEquals(
                LocalizedTextUtil.findDefaultText("struts.messages.error.uploading", Locale.US,
                        new Object[] { "some error messages" }),
                "Error uploading: some error messages");
    }

    public void testPrepareSetEncodingProperly() throws Exception {
        HttpServletRequest req = new MockHttpServletRequest();
        HttpServletResponse res = new MockHttpServletResponse();

        Dispatcher du = initDispatcher(new HashMap() {{
            put(StrutsConstants.STRUTS_I18N_ENCODING, "utf-8");
        }});
        du.prepare(req, res);

        assertEquals(req.getCharacterEncoding(), "utf-8");
    }

    public void testPrepareSetEncodingPropertyWithMultipartRequest() throws Exception {
        MockHttpServletRequest req = new MockHttpServletRequest();
        MockHttpServletResponse res = new MockHttpServletResponse();

        req.setContentType("multipart/form-data");
        Dispatcher du = initDispatcher(new HashMap() {{
            put(StrutsConstants.STRUTS_I18N_ENCODING, "utf-8");
        }});
        du.prepare(req, res);

        assertEquals("utf-8", req.getCharacterEncoding());
    }
    
    public void testDispatcherListener() throws Exception {
    	
    	final DispatcherListenerState state = new DispatcherListenerState();
    	
    	Dispatcher.addDispatcherListener(new DispatcherListener() {
			public void dispatcherDestroyed(Dispatcher du) {
				state.isDestroyed = true;
			}
			public void dispatcherInitialized(Dispatcher du) {
				state.isInitialized = true;
			}
    	});
    	
    	
    	assertFalse(state.isDestroyed);
    	assertFalse(state.isInitialized);
    	
        Dispatcher du = initDispatcher(new HashMap<String, String>() );
    	
    	assertTrue(state.isInitialized);
    	
    	du.cleanup();
    	
    	assertTrue(state.isDestroyed);
    }
    
    
    public void testConfigurationManager() {
    	Dispatcher du = null;
    	InternalConfigurationManager configurationManager = new InternalConfigurationManager();
    	try {
    		du = new Dispatcher(new MockServletContext(), new HashMap<String, String>());
    		du.setConfigurationManager(configurationManager);
    		
    		du.init();
    		
            Dispatcher.setInstance(du);
            
            assertFalse(configurationManager.destroyConfiguration);
            
            du.cleanup();
            
            assertTrue(configurationManager.destroyConfiguration);
            
    	}
    	finally {
    		du.setInstance(null);
    	}
    }
    
    class InternalConfigurationManager extends ConfigurationManager {
    	public boolean destroyConfiguration = false;
    	
    	@Override
    	public synchronized void destroyConfiguration() {
    		super.destroyConfiguration();
    		destroyConfiguration = true;
    	}
    }
    
    
    class DispatcherListenerState {
    	public boolean isInitialized = false;
    	public boolean isDestroyed = false;
    }
}
