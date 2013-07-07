<#include "/${parameters.templateDir}/${parameters.theme}/controlheader.ftl" />

<textarea<#rt/>
 dojoType="Editor2"
<#if parameters.editorControls?exists>
 items="${parameters.editorControls?html}"<#rt/>
<#else>
 items="linkGroup;|;textGroup;|;justifyGroup;|;listGroup;|;indentGroup;|;colorGroup"
</#if>
 name="${parameters.name?default("")?html}"<#rt/>
 cols="${parameters.cols?default("")?html}"<#rt/>
 rows="${parameters.rows?default("")?html}"<#rt/>
<#if parameters.wrap?exists>
 wrap="${parameters.wrap?html}"<#rt/>
</#if>
<#if parameters.disabled?default(false)>
 disabled="disabled"<#rt/>
</#if>
<#if parameters.readonly?default(false)>
 readonly="readonly"<#rt/>
</#if>
<#if parameters.tabindex?exists>
 tabindex="${parameters.tabindex?html}"<#rt/>
</#if>
<#if parameters.id?exists>
 id="${parameters.id?html}"<#rt/>
</#if>
<#if parameters.cssClass?exists>
 class="${parameters.cssClass?html}"<#rt/>
</#if>
<#if parameters.cssStyle?exists>
 style="${parameters.cssStyle?html}"<#rt/>
</#if>
<#if parameters.title?exists>
 title="${parameters.title?html}"<#rt/>
</#if>
<#include "/${parameters.templateDir}/simple/scripting-events.ftl" />
><#rt/>
<#if parameters.nameValue?exists>
<@s.property value="parameters.nameValue"/><#t/>
</#if>
</textarea>

<#--include "/${parameters.templateDir}/xhtml/controlfooter.ftl" /-->
<#include "/${parameters.templateDir}/${themeProperties.parent}/controlfooter.ftl" />
