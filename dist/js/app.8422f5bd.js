(function(e){function t(t){for(var a,o,s=t[0],r=t[1],c=t[2],h=0,g=[];h<s.length;h++)o=s[h],Object.prototype.hasOwnProperty.call(l,o)&&l[o]&&g.push(l[o][0]),l[o]=0;for(a in r)Object.prototype.hasOwnProperty.call(r,a)&&(e[a]=r[a]);u&&u(t);while(g.length)g.shift()();return i.push.apply(i,c||[]),n()}function n(){for(var e,t=0;t<i.length;t++){for(var n=i[t],a=!0,s=1;s<n.length;s++){var r=n[s];0!==l[r]&&(a=!1)}a&&(i.splice(t--,1),e=o(o.s=n[0]))}return e}var a={},l={app:0},i=[];function o(t){if(a[t])return a[t].exports;var n=a[t]={i:t,l:!1,exports:{}};return e[t].call(n.exports,n,n.exports,o),n.l=!0,n.exports}o.m=e,o.c=a,o.d=function(e,t,n){o.o(e,t)||Object.defineProperty(e,t,{enumerable:!0,get:n})},o.r=function(e){"undefined"!==typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},o.t=function(e,t){if(1&t&&(e=o(e)),8&t)return e;if(4&t&&"object"===typeof e&&e&&e.__esModule)return e;var n=Object.create(null);if(o.r(n),Object.defineProperty(n,"default",{enumerable:!0,value:e}),2&t&&"string"!=typeof e)for(var a in e)o.d(n,a,function(t){return e[t]}.bind(null,a));return n},o.n=function(e){var t=e&&e.__esModule?function(){return e["default"]}:function(){return e};return o.d(t,"a",t),t},o.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},o.p="";var s=window["webpackJsonp"]=window["webpackJsonp"]||[],r=s.push.bind(s);s.push=t,s=s.slice();for(var c=0;c<s.length;c++)t(s[c]);var u=r;i.push([0,"chunk-vendors"]),n()})({0:function(e,t,n){e.exports=n("56d7")},"0e05":function(e,t,n){},2403:function(e,t,n){"use strict";n("d687")},"33b3":function(e,t,n){},"3fae":function(e,t,n){"use strict";n("f5da")},"4b42":function(e,t,n){"use strict";n("7255")},"56d7":function(e,t,n){"use strict";n.r(t);n("e260"),n("e6cf"),n("cca6"),n("a79d");var a=n("2b0e"),l=function(){var e=this,t=e.$createElement,n=e._self._c||t;return n("div",{attrs:{id:"app"}},[n("keep-alive",[e.$route.meta.keepAlive?n("router-view"):e._e()],1),e.$route.meta.keepAlive?e._e():n("router-view")],1)},i=[],o=(n("caad"),n("2532"),n("ac1f"),n("1276"),n("fb6a"),n("d3b7"),n("bc3a")),s=n.n(o),r=n("5c96"),c=n.n(r),u=void 0;function h(e,t){var n=arguments.length>2&&void 0!==arguments[2]?arguments[2]:"";return new Promise((function(a,l){s.a.get(e+n,{params:t}).then((function(e){a(e.data)})).catch((function(e){l(e.data)}))}))}s.a.defaults.retry=3,s.a.defaults.retryDelay=1e3,s.a.defaults.timeout=1e5,s.a.defaults.baseURL="/api",s.a.defaults.headers.post["Content-Type"]="application/x-www-form-urlencoded",s.a.interceptors.request.use((function(e){return e}),(function(e){return console.log(e),Promise.reject(e)})),s.a.interceptors.response.use((function(e){if(200===e.status)return Promise.resolve(e)}),(function(e){if(e.response.status)switch(e.response.status){case 500:break;case 401:r["Message"].error("无权限");break;case 404:r["Message"].error("当前接口不存在");break;default:return u.$message.error(e.response.message),Promise.reject(e.response)}}));var g=function(e){return h("/v1/todo/",e)},d=function(e){return h("/v1/todo/total",e)},f=function(e){return h("/v1/todo/ping",e)},p={name:"app",data:function(){return{webSocket:null,logArr:[],timer1:"",isConnect:!0}},created:function(){this.initWebSocket()},mounted:function(){var e=this;this.timer1=setInterval((function(){e.isConnect&&(e.isConnect=!1,f().then((function(){e.$store.commit("changeSqlConnect",!0),e.isConnect=!0})).catch((function(){e.$store.commit("changeSqlConnect",!1),e.isConnect=!0})))}),1e3)},destroyed:function(){this.webSocket.close()},beforeDestroy:function(){clearInterval(this.timer1)},close:function(){this.webSocket.close()},methods:{initWebSocket:function(){var e=localStorage.getItem("websocketIp"),t=localStorage.getItem("websocketPort");this.webSocket=new WebSocket("ws://"+e+":"+t),this.$store.commit("changeWebSocket",this.webSocket),this.webSocket.onopen=this.onOpen,this.webSocket.onmessage=this.onMessage,this.webSocket.onerror=this.onError,this.webSocket.onclose=this.onClose},onMessage:function(e){if("{"!=e.data[0]){var t=this.cutString(e);this.logArr.includes(t.file)||(this.logArr.push(t.file),this.$store.commit("changeLog",{title:t.file,content:[]}),this.$store.commit("changeFile",{title:t.file,total:0}));var n=this.logArr.indexOf(t.file);switch(this.$store.commit("changeTotal"),this.$store.commit("changeLogContent",{logIndex:n,log:t}),this.$store.commit("changeFileTotal",n),this.$store.commit("changeMonthTotal",new Date(t.date).getMonth()),t.level){case"debug":this.$store.commit("changeLevelTotal",0);break;case"info":this.$store.commit("changeLevelTotal",1);break;case"warning":this.$store.commit("changeLevelTotal",2);break;case"error":this.$store.commit("changeLevelTotal",3);break}}else this.$store.commit("changeSetting",JSON.parse(e.data))},cutString:function(e){var t=new String,n=new Array;t=e.data,n=t.split(" ");var a=n[0].length+n[1].length+n[2].length+n[3].length+4;return{date:n[0].slice(1,n[0].length),time:n[1].slice(0,n[1].length-1),file:n[2].slice(1,n[2].length-1),level:n[3].slice(1,n[3].length-1),message:t.slice(a)}},onOpen:function(){},onError:function(){this.initWebSocket()},onClose:function(){}}},m=p,b=n("2877"),v=Object(b["a"])(m,l,i,!1,null,null,null),w=v.exports,k=n("8c4f"),S=function(){var e=this,t=e.$createElement,n=e._self._c||t;return n("div",{staticClass:"home"},[n("SideMenu",{staticClass:"home-left"}),n("div",{staticClass:"home-right"},[n("el-empty",{directives:[{name:"show",rawName:"v-show",value:e.isConnected,expression:"isConnected"}],staticClass:"empty",attrs:{description:"连接不到websocket"}}),n("el-tabs",{directives:[{name:"show",rawName:"v-show",value:!e.isConnected,expression:"!isConnected"}],attrs:{type:"card"},model:{value:e.editableTabsValue,callback:function(t){e.editableTabsValue=t},expression:"editableTabsValue"}},e._l(e.editableTabs,(function(t){return n("el-tab-pane",{key:t.name,attrs:{label:t.title,name:t.name,align:"left"}},[n("el-row",{attrs:{type:"flex",justify:"start"}},[n("el-date-picker",{attrs:{"unlink-panels":"",size:"mini",type:"daterange","range-separator":"至","start-placeholder":"开始日期","end-placeholder":"结束日期"},model:{value:e.value1,callback:function(t){e.value1=t},expression:"value1"}}),n("JsonExcel",{attrs:{data:t.content,fields:e.json_fields,name:t.title+e.generateTimeReqestNumber()}},[n("el-button",{attrs:{size:"mini",icon:"el-icon-download"},on:{click:function(n){return e.clickHandler(t,n)}}})],1),n("el-input",{staticStyle:{width:"300px","margin-left":"900px"},attrs:{size:"mini",placeholder:"输入关键字搜索"},on:{change:function(n){return e.handleSearch(t)}},model:{value:e.input,callback:function(t){e.input=t},expression:"input"}},[n("el-dropdown",{attrs:{slot:"prepend",trigger:"click",placement:"bottom"},slot:"prepend"},[n("el-button",{attrs:{size:"mini",icon:"el-icon-menu"}}),n("el-dropdown-menu",{attrs:{slot:"dropdown"},slot:"dropdown"},[n("el-checkbox",{model:{value:e.isDate,callback:function(t){e.isDate=t},expression:"isDate"}},[e._v("日期")]),n("el-checkbox",{model:{value:e.isTime,callback:function(t){e.isTime=t},expression:"isTime"}},[e._v("时间")]),n("el-checkbox",{model:{value:e.isFile,callback:function(t){e.isFile=t},expression:"isFile"}},[e._v("模块")]),n("el-checkbox",{model:{value:e.isLevel,callback:function(t){e.isLevel=t},expression:"isLevel"}},[e._v("级别")]),n("el-checkbox",{model:{value:e.isLog,callback:function(t){e.isLog=t},expression:"isLog"}},[e._v("内容")])],1)],1),n("el-button",{attrs:{slot:"append",icon:"el-icon-search"},on:{click:e.handleSearch},slot:"append"})],1)],1),n("el-table",{attrs:{border:"","max-height":e.fullHeight,data:t.content.filter((function(t){return!e.search||t.message.toLowerCase().includes(e.search.toLowerCase())})).filter((function(t){return!e.value1||new Date(t.date).getTime()-288e5>=e.value1[0].getTime()&&new Date(t.date).getTime()-288e5<=e.value1[1].getTime()})).slice((t.currentPage-1)*e.pagesize,t.currentPage*e.pagesize),"header-cell-style":{"text-align":"center"}}},[e.isDate?n("el-table-column",{attrs:{width:"200",prop:"date",label:"日期",align:"center"}}):e._e(),e.isTime?n("el-table-column",{attrs:{width:"200",prop:"time",label:"时间",align:"center"}}):e._e(),e.isFile?n("el-table-column",{attrs:{width:"200",prop:"file",label:"模块",align:"center"}}):e._e(),e.isLevel?n("el-table-column",{attrs:{width:"200",prop:"level",label:"级别","column-key":"date",align:"center",filters:[{text:"info",value:"info"},{text:"debug",value:"debug"},{text:"warning",value:"warning"},{text:"error",value:"error"}],"filter-method":e.filterHandler}}):e._e(),e.isLog?n("el-table-column",{attrs:{prop:"message",label:"内容",align:"left"},scopedSlots:e._u([{key:"default",fn:function(t){return[n("label",{domProps:{innerHTML:e._s(e.sensitiveWords(t.row.message))}})]}}],null,!0)}):e._e()],1),n("el-pagination",{attrs:{"current-page":t.currentPage,"page-sizes":[5,10,20,40],"page-size":e.pagesize,layout:"total, sizes, prev, pager, next, jumper",total:t.content.filter((function(t){return!e.search||t.message.toLowerCase().includes(e.search.toLowerCase())})).filter((function(t){return!e.value1||new Date(t.date).getTime()-288e5>=e.value1[0].getTime()&&new Date(t.date).getTime()-288e5<=e.value1[1].getTime()})).length,align:"center"},on:{"size-change":e.handleSizeChange,"current-change":function(n){return e.handleCurrentChange(t,n)},"update:currentPage":function(n){return e.$set(t,"currentPage",n)},"update:current-page":function(n){return e.$set(t,"currentPage",n)}}},[e._v(" //这是显示总共有多少数据 ")])],1)})),1)],1)],1)},x=[],T=(n("99af"),n("4d63"),n("c607"),n("2c3e"),n("25f0"),n("5319"),n("841c"),function(){var e=this,t=e.$createElement,n=e._self._c||t;return n("el-menu",{staticClass:"side-menu",attrs:{"default-active":e.activeIndex,router:!0,collapse:e.isCollapse,"background-color":"#545c64","text-color":"#fff","active-text-color":"#ffd04b"}},[n("div",{staticClass:"fold-wrapper"},[e.isCollapse?n("i",{staticClass:"el-icon-s-unfold",attrs:{title:"展开"},on:{click:function(t){e.isCollapse=!1}}}):n("i",{staticClass:"el-icon-s-fold",attrs:{title:"收缩"},on:{click:function(t){e.isCollapse=!0}}})]),n("el-menu-item",{attrs:{index:"About"}},[n("i",{staticClass:"el-icon-odometer"}),n("span",{attrs:{slot:"title"},slot:"title"},[e._v("仪表板")])]),n("el-menu-item",{attrs:{index:"Home"}},[n("i",{staticClass:"el-icon-reading"}),n("span",{attrs:{slot:"title"},slot:"title"},[e._v("日志")])]),n("el-menu-item",{attrs:{index:"Logorm"}},[n("i",{staticClass:"el-icon-data-line"}),n("span",{attrs:{slot:"title"},slot:"title"},[e._v("数据库")])]),n("el-menu-item",{attrs:{index:"Setting"}},[n("i",{staticClass:"el-icon-setting"}),n("span",{attrs:{slot:"title"},slot:"title"},[e._v("设置")])]),n("el-alert",{directives:[{name:"show",rawName:"v-show",value:this.$store.state.sqlConnect,expression:"this.$store.state.sqlConnect"}],staticStyle:{bottom:"0%",position:"absolute"},attrs:{title:"成功连接",type:"success",closable:!1,"show-icon":"",effect:"dark"}}),n("el-alert",{directives:[{name:"show",rawName:"v-show",value:!this.$store.state.sqlConnect,expression:"!this.$store.state.sqlConnect"}],staticStyle:{bottom:"0%",position:"absolute"},attrs:{title:"连接失败",type:"error",closable:!1,"show-icon":"",effect:"dark"}})],1)}),C=[],y=(n("b0c0"),{name:"SideMenu",data:function(){return{isCollapse:!1}},computed:{activeIndex:function(){return String(this.$route.name)}},watch:{isCollapse:function(e){sessionStorage.setItem("isCollapse",e)}},created:function(){this.isCollapse="true"===sessionStorage.getItem("isCollapse")}}),P=y,_=(n("eff8"),Object(b["a"])(P,T,C,!1,null,"271d9e70",null)),$=_.exports,O=n("f2d9"),I=n("f8b4"),E=n.n(I),L={name:"home",components:{SideMenu:$,JsonExcel:O["a"]},data:function(){return{editableTabsValue:"0",editableTabs:[],tabIndex:0,logArr:[],content:[],timer:"",pagesize:10,search:"",input:"",value1:"",isConnected:!0,fullHeight:document.documentElement.clientHeight-150,isDate:!0,isTime:!0,isFile:!0,isLevel:!0,isLog:!0,json_fields:{"日期":"date","时间":"time","模块":"file","级别":"level","内容":"message"}}},created:function(){},mounted:function(){var e=this;this.timer=setInterval((function(){for(var t=e.$store.state.log,n=e.logArr.length;n<t.length;n++){e.logArr.push(t[n].title);var a=++e.tabIndex+"";e.editableTabs.push({currentPage:1,title:t[n].title,name:a,content:[]}),e.editableTabsValue=a,e.isConnected=!1}for(n=0;n<t.length;n++)e.editableTabs[n].content=[].concat(t[n].content)}),100)},beforeDestroy:function(){clearInterval(this.timer)},destroyed:function(){},methods:{sensitiveWords:function(e){var t=new RegExp(this.input,"g");return e=e.replace(t,'<font color="red">'+this.input+"</font>"),e},generateTimeReqestNumber:function(){var e=new Date;return e.getFullYear().toString()+this.pad2(e.getMonth()+1)+this.pad2(e.getDate())+this.pad2(e.getHours())+this.pad2(e.getMinutes())+this.pad2(e.getSeconds())},pad2:function(e){return e<10?"0"+e:e},clickHandler:function(e,t){E.a.downloadCsv(e.content,this.json_fields,e.title+this.generateTimeReqestNumber());var n=t.target;"I"==n.nodeName&&(n=t.target.parentNode),n.blur()},handleSizeChange:function(e){this.pagesize=e},handleCurrentChange:function(e,t){e.currentPage=t},handleSearch:function(){this.search=this.input},filterHandler:function(e,t,n){var a=n["property"];return t[a]===e}}},D=L,M=(n("4b42"),Object(b["a"])(D,S,x,!1,null,"4fb7ebb5",null)),z=M.exports,A=function(){var e=this,t=e.$createElement,n=e._self._c||t;return n("div",{staticClass:"about"},[n("SideMenu",{staticClass:"about-left"}),n("div",{staticClass:"about-right"},[n("el-row",{staticClass:"home",attrs:{gutter:20}},[n("el-col",{attrs:{span:8}},[n("el-card",{staticStyle:{height:"200px"},attrs:{shadow:"hover"}},[n("div",{staticClass:"total"},[n("div",[n("p",{staticStyle:{"line-height":"0px","font-size":"10px"}},[e._v("所有日志")]),n("p",{staticStyle:{"line-height":"0px","font-size":"30px"}},[e._v(" "+e._s(this.lsSqlTotal)+" ")]),n("p",{staticStyle:{color:"green"}},[e._v(" ▲"+e._s(this.lsSqlTotal-this.sqlTotal)+"("+e._s(((this.lsSqlTotal-this.sqlTotal)/1e4).toFixed(2))+"%) ")])]),n("div",{staticStyle:{border:"1px solid #000",height:"110px"}}),n("div",[n("p",{staticStyle:{"line-height":"0px","font-size":"10px"}},[e._v("缓存日志")]),n("p",{staticStyle:{"line-height":"0px","font-size":"30px"}},[e._v(" "+e._s(this.lsTotal)+" ")]),n("p",{staticStyle:{color:"green"}},[e._v(" ▲"+e._s(this.lsTotal-this.total)+"("+e._s(((this.lsTotal-this.total)/1e4).toFixed(2))+"%) ")])])])]),n("el-card",{staticStyle:{height:"300px","margin-top":"20px"},attrs:{shadow:"hover"}},[n("ve-line",{attrs:{height:"300px",data:e.chartData,colors:e.colors,extend:e.chartExtend,settings:e.chartSettings}})],1),n("el-card",{staticStyle:{height:"275px","margin-top":"20px"},attrs:{shadow:"hover"}},[n("ve-pie",{attrs:{data:e.pieData,settings:e.pieSettings,extend:e.pieExtend}})],1)],1),n("el-col",{attrs:{span:16}},[n("el-card",{attrs:{shadow:"hover"}},[n("div",{staticStyle:{height:"280px"}})]),n("div",{staticClass:"graph"},[n("el-card",{staticStyle:{height:"400px","margin-top":"20px"},attrs:{shadow:"hover"}},[n("ve-histogram",{attrs:{height:"400px",data:e.histogramData,settings:e.histogramSettings,extend:e.histogramExtend}})],1)],1)],1)],1)],1)],1)},q=[],R=(n("627c"),{name:"about",components:{SideMenu:$},data:function(){return this.colors=["#87CEFA"],this.chartExtend={series:{smooth:!1},legend:{show:!1},title:{text:"日志趋势",x:"left",y:"top",textAlign:"auto",textStyle:{color:"#000000",fontWeight:"normal",fontSize:12}}},this.chartSettings={area:!0,scale:[!0]},this.pieSettings={type:"pie"},this.pieExtend={series:{center:["30%","30%"],radius:"40%",minAngle:15},legend:{type:"scroll",orient:"vertical",show:!0,left:"70%",top:70},title:{text:"日志比例",x:"left",y:"top",textAlign:"auto",textStyle:{color:"#000000",fontWeight:"normal",fontSize:12}}},this.histogramSettings={type:"histogram"},this.histogramExtend={series:{barWidth:30},legend:{show:!1},title:{text:"日志数量",x:"left",y:"top",textAlign:"auto",textStyle:{color:"#000000",fontWeight:"normal",fontSize:12}}},{timer1:"",timer2:"",lsTotal:0,total:1,sqlTotal:0,lsSqlTotal:0,sqlConnect:!1,chartData:{columns:["月份","日志数"],rows:[{"月份":"1","日志数":"0"},{"月份":"2","日志数":"0"},{"月份":"3","日志数":"0"},{"月份":"4","日志数":"0"},{"月份":"5","日志数":"0"}]},pieData:{columns:["key","value"],rows:[{key:"debug",value:"0"},{key:"info",value:"0"},{key:"warning",value:"0"},{key:"error",value:"0"}]},histogramData:{columns:["key","value"],rows:[]}}},mounted:function(){var e=this;d().then((function(t){e.sqlTotal=t.total,e.lsSqlTotal=t.total})).catch((function(){}));var t=this;this.timer1=setInterval((function(){t.$store.state.sqlConnect&&d().then((function(e){t.lsSqlTotal=e.total})).catch((function(){}))}),1e4),this.timer2=setInterval((function(){if(t.$store.state.total>t.lsTotal){t.lsTotal=t.$store.state.total;for(var e=new Date,n=0;n<5;n++){var a=(e.getMonth()+13-4+n)%12==0?12:(e.getMonth()+13-4+n)%12;t.$set(t.chartData.rows,n,{"月份":a+"","日志数":t.$store.state.monthTotal[a-1]+""})}for(n=0;n<4;n++)t.$set(t.pieData.rows[n],"value",t.$store.state.levelTotal[n]+"");for(n=t.histogramData.rows.length;n<t.$store.state.fileTotal.length;n++)t.histogramData.rows.push({key:t.$store.state.fileTotal[n].title,value:"0"});for(n=0;n<t.$store.state.fileTotal.length;n++)t.$set(t.histogramData.rows[n],"value",t.$store.state.fileTotal[n].total+"")}}),100)},beforeDestroy:function(){clearInterval(this.timer1),clearInterval(this.timer2)}}),H=R,F=(n("e76e"),n("2403"),Object(b["a"])(H,A,q,!1,null,"71a6a6e9",null)),N=F.exports,j=function(){var e=this,t=e.$createElement,n=e._self._c||t;return n("div",{staticClass:"Setting"},[n("SideMenu",{staticClass:"Setting-left"}),n("div",{staticClass:"Setting-right"},[n("el-result",{directives:[{name:"show",rawName:"v-show",value:e.result,expression:"result"}],attrs:{icon:"success",title:"修改成功"}},[n("template",{slot:"extra"},[n("el-button",{attrs:{type:"primary",size:"medium"},on:{click:e.onReturn}},[e._v("返回")])],1)],2),n("div",{directives:[{name:"show",rawName:"v-show",value:!e.result,expression:"!result"}]},[n("el-collapse",{model:{value:e.activeNames,callback:function(t){e.activeNames=t},expression:"activeNames"}},[n("el-collapse-item",{attrs:{title:"浏览器(刷新生效)",name:"1"}},[n("el-form",{ref:"form",staticStyle:{width:"450px"},attrs:{model:e.form,"label-width":"150px"}},[n("el-form-item",{attrs:{label:"webSocket ip"}},[n("el-input",{model:{value:e.form.websocketIp,callback:function(t){e.$set(e.form,"websocketIp",t)},expression:"form.websocketIp"}})],1),n("el-form-item",{attrs:{label:"webSocket 端口"}},[n("el-input",{model:{value:e.form.websocketPort,callback:function(t){e.$set(e.form,"websocketPort",t)},expression:"form.websocketPort"}})],1)],1)],1),n("el-collapse-item",{attrs:{title:"配置",name:"2"}},[n("el-form",{ref:"form",staticStyle:{width:"450px"},attrs:{model:e.form,"label-width":"170px"}},[n("el-form-item",{attrs:{label:"模式"}},[n("el-checkbox-group",{model:{value:e.checkList,callback:function(t){e.checkList=t},expression:"checkList"}},[n("el-checkbox",{attrs:{label:"tcp",disabled:!this.$store.state.sqlConnect}}),n("el-checkbox",{attrs:{label:"websocket"}}),n("el-checkbox",{attrs:{label:"file"}})],1)],1),n("el-form-item",{attrs:{label:"缓存日志条数"}},[n("el-input",{model:{value:e.setting.BUFFERSIZE,callback:function(t){e.$set(e.setting,"BUFFERSIZE",t)},expression:"setting.BUFFERSIZE"}})],1),n("el-form-item",{attrs:{label:"本地存储文件数量"}},[n("el-input",{model:{value:e.setting.MAXFILES,callback:function(t){e.$set(e.setting,"MAXFILES",t)},expression:"setting.MAXFILES"}})],1),n("el-form-item",{attrs:{label:"本地存储文件大小(M)"}},[n("el-input",{model:{value:e.setting.MAXSIZE,callback:function(t){e.$set(e.setting,"MAXSIZE",t)},expression:"setting.MAXSIZE"}})],1),n("el-form-item",{attrs:{label:"归集服务器ip"}},[n("el-input",{model:{value:e.setting.TCPIP,callback:function(t){e.$set(e.setting,"TCPIP",t)},expression:"setting.TCPIP"}})],1),n("el-form-item",{attrs:{label:"归集服务器sinkPort"}},[n("el-input",{model:{value:e.setting.TCPSINKPORT,callback:function(t){e.$set(e.setting,"TCPSINKPORT",t)},expression:"setting.TCPSINKPORT"}})],1),n("el-form-item",{attrs:{label:"归集服务器httpPort"}},[n("el-input",{model:{value:e.setting.TCPHTTPPORT,callback:function(t){e.$set(e.setting,"TCPHTTPPORT",t)},expression:"setting.TCPHTTPPORT"}})],1),n("el-form-item",{attrs:{label:"WebSocketPort(重启)"}},[n("el-input",{model:{value:e.setting.WEBSOCKETPORT,callback:function(t){e.$set(e.setting,"WEBSOCKETPORT",t)},expression:"setting.WEBSOCKETPORT"}})],1),n("el-form-item",{attrs:{label:"web服务器Port(重启)"}},[n("el-input",{model:{value:e.setting.HTTPPORT,callback:function(t){e.$set(e.setting,"HTTPPORT",t)},expression:"setting.HTTPPORT"}})],1)],1)],1)],1),n("el-button",{staticStyle:{position:"absolute",left:"50%"},attrs:{type:"primary"},on:{click:e.onSubmit}},[e._v("确定")])],1)],1)],1)},W=[],B=(n("e9c4"),{name:"Setting",components:{SideMenu:$},data:function(){return{activeNames:["1","2"],form:{websocketIp:"",websocketPort:""},setting:{BUFFERSIZE:"",MAXFILES:"",MAXSIZE:"",MODE:"",TCPHTTPPORT:"",TCPIP:"",TCPSINKPORT:"",WEBSOCKETPORT:"",HTTPPORT:""},result:!1,checkList:[]}},mounted:function(){this.form.websocketIp=localStorage.getItem("websocketIp")?localStorage.getItem("websocketIp"):window.location.hostname,this.form.websocketPort=localStorage.getItem("websocketPort")?localStorage.getItem("websocketPort"):"9002",this.setting=this.$store.state.setting,1&this.setting.MODE&&this.checkList.push("tcp"),2&this.setting.MODE&&this.checkList.push("websocket"),4&this.setting.MODE&&this.checkList.push("file")},methods:{onSubmit:function(){localStorage.clear(),localStorage.setItem("websocketIp",this.form.websocketIp),localStorage.setItem("websocketPort",this.form.websocketPort),this.setting.MODE=0,-1!=this.checkList.indexOf("tcp")&&this.$store.state.sqlConnect&&(this.setting.MODE+=1),-1!=this.checkList.indexOf("websocket")&&(this.setting.MODE+=2),-1!=this.checkList.indexOf("file")&&(this.setting.MODE+=4),this.setting.MODE=""+this.setting.MODE,this.result=!0;var e=this.$store.state.webSocket;e.send(JSON.stringify(this.setting))},onReturn:function(){this.result=!1}}}),K=B,X=(n("3fae"),Object(b["a"])(K,j,W,!1,null,"fc7dd15e",null)),Z=X.exports,J=function(){var e=this,t=e.$createElement,n=e._self._c||t;return n("div",{staticClass:"Logorm"},[n("SideMenu",{staticClass:"Logorm-left"}),n("div",{staticClass:"Logorm-right"},[n("el-row",[n("el-form",{attrs:{inline:!0,size:"mini"}},[n("el-form-item",[n("el-date-picker",{attrs:{type:"datetimerange","range-separator":"至","start-placeholder":"开始日期","end-placeholder":"结束日期","value-format":"timestamp"},model:{value:e.value1,callback:function(t){e.value1=t},expression:"value1"}})],1),n("el-form-item",{attrs:{label:"模块"}},[n("el-input",{attrs:{placeholder:"请输入模块名"},model:{value:e.logger,callback:function(t){e.logger=t},expression:"logger"}})],1),n("el-form-item",{attrs:{label:"级别"}},[n("el-select",{attrs:{placeholder:"请选择级别",clearable:""},model:{value:e.level,callback:function(t){e.level=t},expression:"level"}},e._l(e.options,(function(e){return n("el-option",{key:e.value,attrs:{label:e.label,value:e.value}})})),1)],1),n("el-form-item",{staticStyle:{width:"6%"}},[n("el-select",{model:{value:e.order,callback:function(t){e.order=t},expression:"order"}},e._l(e.optionsOrder,(function(e){return n("el-option",{key:e.value,attrs:{label:e.label,value:e.value}})})),1)],1),n("el-form-item",{attrs:{label:"内容"}},[n("el-input",{attrs:{placeholder:"请输入搜索关键字"},model:{value:e.input,callback:function(t){e.input=t},expression:"input"}})],1),n("el-form-item",[n("el-button",{attrs:{disabled:e.isDisabled},on:{click:e.clickSearch}},[e._v("搜索")])],1)],1)],1),n("el-table",{directives:[{name:"loading",rawName:"v-loading",value:e.loading,expression:"loading"}],attrs:{data:e.message,border:"","max-height":e.fullHeight,"header-cell-style":{"text-align":"center"}}},[n("el-table-column",{attrs:{prop:"time",label:"时间",width:"300",align:"center"}}),n("el-table-column",{attrs:{prop:"logger",label:"模块",width:"200",align:"center"}}),n("el-table-column",{attrs:{prop:"level",label:"级别","column-key":"date",width:"200",align:"center",filters:[{text:"info",value:"info"},{text:"debug",value:"debug"},{text:"warning",value:"warning"},{text:"error",value:"error"}],"filter-method":e.filterHandler}}),n("el-table-column",{attrs:{prop:"log",label:"内容",align:"left"},scopedSlots:e._u([{key:"default",fn:function(t){return[n("label",{domProps:{innerHTML:e._s(e.sensitiveWords(t.row.log))}})]}}])})],1),n("el-pagination",{attrs:{"current-page":e.currentPage,"page-sizes":[5,10,20,40],"page-size":e.pagesize,layout:"total, sizes, prev, pager, next, jumper",total:e.total,disabled:e.isDisabled,align:"center"},on:{"size-change":e.handleSizeChange,"current-change":e.handleCurrentChange,"update:currentPage":function(t){e.currentPage=t},"update:current-page":function(t){e.currentPage=t}}},[e._v(" //这是显示总共有多少数据 ")])],1)],1)},U=[],V={name:"Logorm",components:{SideMenu:$},data:function(){return{options:[{value:"info",label:"info"},{value:"debug",label:"debug"},{value:"warning",label:"warning"},{value:"error",label:"error"}],optionsOrder:[{value:"asc",label:"正序"},{value:"desc",label:"倒序"}],order:"asc",logger:"",input:"",level:"",message:[],currentPage:1,pagesize:10,total:0,fullHeight:document.documentElement.clientHeight-150,loading:!1,id:0,value1:null,isDisabled:!1}},methods:{sensitiveWords:function(e){var t=new RegExp(this.input,"g");return e=e.replace(t,'<font color="red">'+this.input+"</font>"),e},search:function(){var e=this;this.loading=!0,this.isDisabled=!0,g({id:this.id,beginTime:this.value1?this.value1[0]:0,endTime:this.value1?this.value1[1]:0,file:this.logger,level:this.level,log:this.input,order:this.order,pageSize:this.pagesize,pageNum:this.currentPage}).then((function(t){e.message=t.data.slice(),e.total=t.total,e.loading=!1,e.isDisabled=!1}))},clickSearch:function(){var e=this;this.loading=!0,this.currentPage=1,this.isDisabled=!0,g({beginTime:this.value1?this.value1[0]:0,endTime:this.value1?this.value1[1]:0,file:this.logger,level:this.level,log:this.input,order:this.order,pageSize:this.pagesize,pageNum:this.currentPage}).then((function(t){e.message=t.data.slice(),e.total=t.total,e.loading=!1,e.isDisabled=!1,e.id=0!=e.message.length?e.message[0].ID:0}))},filterHandler:function(e,t,n){var a=n["property"];return t[a]===e},handleSizeChange:function(e){this.pagesize=e,this.search()},handleCurrentChange:function(e){this.currentPage=e,this.search()}}},Y=V,G=(n("9277"),Object(b["a"])(Y,J,U,!1,null,"3f46aa5b",null)),Q=G.exports;a["default"].use(k["a"]);var ee=[{path:"/",name:"Aboud",component:N,meta:{keepAlive:!0}},{path:"/About",name:"About",component:N,meta:{keepAlive:!0}},{path:"/Home",name:"Home",component:z,meta:{keepAlive:!0}},{path:"/Logorm",name:"Logorm",component:Q,meta:{keepAlive:!0}},{path:"/Setting",name:"Setting",component:Z}],te=new k["a"]({base:"",routes:ee}),ne=te,ae=n("2f62");n("54ba");a["default"].use(ae["a"]);var le=new ae["a"].Store({state:{log:[],total:0,monthTotal:[0,0,0,0,0,0,0,0,0,0,0,0],levelTotal:[0,0,0,0],fileTotal:[],webSocket:WebSocket,setting:{},sqlConnect:!1},getters:{log:function(e){return e.log},total:function(e){return e.total},monthTotal:function(e){return e.monthTotal},levelTotal:function(e){return e.levelTotal},fileTotal:function(e){return e.fileTotal},webSocket:function(e){return e.webSocket},setting:function(e){return e.setting},sqlConnect:function(e){return e.sqlConnect}},mutations:{changeLog:function(e,t){e.log.push(t)},changeLogContent:function(e,t){e.log[t.logIndex].content.unshift(t.log)},changeTotal:function(e){e.total+=1},changeMonthTotal:function(e,t){e.monthTotal[t]++},changeLevelTotal:function(e,t){e.levelTotal[t]++},changeFile:function(e,t){e.fileTotal.push(t)},changeFileTotal:function(e,t){e.fileTotal[t].total++},changeWebSocket:function(e,t){e.webSocket=t},changeSetting:function(e,t){e.setting=t},changeSqlConnect:function(e,t){e.sqlConnect=t},clear:function(e){e.log=[],e.total=0,e.monthTotal=[0,0,0,0,0,0,0,0,0,0,0,0],e.levelTotal=[0,0,0,0],e.fileTotal=[],e.webSocket=null,e.setting={}}},actions:{},modules:{}}),ie=(n("0fae"),n("2819")),oe=n.n(ie);a["default"].config.productionTip=!1,a["default"].use(c.a),a["default"].use(oe.a),new a["default"]({router:ne,store:le,render:function(e){return e(w)}}).$mount("#app")},7255:function(e,t,n){},"91aa":function(e,t,n){},9277:function(e,t,n){"use strict";n("33b3")},d687:function(e,t,n){},e76e:function(e,t,n){"use strict";n("91aa")},eff8:function(e,t,n){"use strict";n("0e05")},f5da:function(e,t,n){}});
//# sourceMappingURL=app.8422f5bd.js.map