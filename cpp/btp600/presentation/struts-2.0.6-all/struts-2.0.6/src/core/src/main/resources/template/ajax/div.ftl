<div dojoType="struts:BindDiv"
  <#if parameters.delay?exists>
    delay="${parameters.delay?c}"<#rt/>
  </#if>
  <#if parameters.updateFreq?exists>
    updateFreq="${parameters.updateFreq?c}"<#rt/>
  </#if>
  <#if parameters.autoStart?exists>
    autoStart="${parameters.autoStart?string?html}"<#rt/>
  </#if>
  <#if parameters.startTimerListenTopics?if_exists != "">
    startTimerListenTopics="${parameters.startTimerListenTopics?html}"<#rt/>
  </#if>
  <#if parameters.stopTimerListenTopics?if_exists != "">
    stopTimerListenTopics="${parameters.stopTimerListenTopics?html}"<#rt/>
  </#if>
  <#if parameters.refreshOnShow?exists>
    refreshOnShow="${parameters.refreshOnShow?string?html}"<#rt/>
  </#if>
  <#include "/${parameters.templateDir}/ajax/ajax-common.ftl" />
  <#include "/${parameters.templateDir}/simple/scripting-events.ftl" />
>
