// This program is a part of NT mudlib

#include <ansi.h>
#include <mudlib.h>
#include <time.h>

//----------------------------------------------------------------------
// 白底色 HEADER ----------------------------------------------------------------------
//----------------------------------------------------------------------
string WHITE_HEADER = @LONG
<html>
<!-- Created by 笑傲江湖 %^UPDATETIME%^ -->
<head>
  <meta http-equiv=Content-Type content="text/html; charset=gb2312">
  %^REFRESH%^
  <title>%^TITLE%^</title>
<style><!--
 a{text-decoration:none}
        -->
  </style>
</head>
<body bgcolor="#ffffff" text="#55555" link="#666688" vlink="#666688">
<table width=80% align=center>
  <tr>
    <td align=center style='font-familiy:verdana;font-size:15px;color:#555;'>本頁面由MUD系統自動建置，更新時間為 %^UPDATETIME%^</td>
  </tr>
</table>
<hr width=80% align=center><p>
LONG;


//----------------------------------------------------------------------
// 黑底色 HEADER ----------------------------------------------------------------------
//----------------------------------------------------------------------
string BLACK_HEADER = @LONG
<html>
<!-- Created by 笑傲江湖 %^UPDATETIME%^ -->
<head>
  <meta http-equiv=Content-Type content="text/html; charset=gb2312">
  %^REFRESH%^
  <title>%^TITLE%^</title>
<style><!--
 a{text-decoration:none}
        -->
  </style>
</head>
<body bgcolor="#000000" text="#bbbbbb" link="#666688" vlink="#666688">
<table width=80% align=center>
  <tr>
    <td align=center style='font-familiy:verdana;font-size:15px;color:#bbb;'>本頁面由MUD系統自動建置，更新時間為 %^UPDATETIME%^</td>
  </tr>
</table>
<hr width=80% align=center><p>
LONG;


//----------------------------------------------------------------------
// 白底色 FOOTER ----------------------------------------------------------------------
//----------------------------------------------------------------------
string WHITE_FOOTER = @LONG
<p><hr width=80% align=center>
<table width=80% align=center>
  <tr>
    <td align=center><font face=verdana size=2 color=555555>Copyright &copy;2000-%^YEAR%^ <a href="http://www.muds.cn"><font color=111111><u>笑傲江湖</u></a> <font color=555555> All Rights Reserved</font></td>

  </tr>
</table>
</body>
</html>
<!-- Created by 笑傲江湖 %^UPDATETIME%^ -->
LONG;

//----------------------------------------------------------------------
// 黑底色 FOOTER ----------------------------------------------------------------------
//----------------------------------------------------------------------
string BLACK_FOOTER = @LONG
<p><hr width=80% align=center>
<table width=80% align=center>
  <tr>
    <td align=center><font face=verdana size=2 color=bbbbbb>Copyright &copy;2000-%^YEAR%^ <a href="http://www.muds.cn"><font color=fffff><u>笑傲江湖</u></a> <font color=bbbbbb> All Rights Reserved</font></td>

  </tr>
</table>
</body>
</html>
<!-- Created by 笑傲江湖 %^UPDATETIME%^ -->
LONG;

//----------------------------------------------------------------------
// JAVA Script ----------------------------------------------------------------------
//----------------------------------------------------------------------
string JAVA_SCRIPT = @long
<script language="JavaScript">
<!--
function show(e, helpmsg)
{
	if(document.layers)
	{
		x = e.layerX;
		y = e.layerY;
		document.layers[0].document.open();
		document.layers[0].document.write(helpmsg);
		document.layers[0].document.close();
		document.layers[0].moveTo(x + 10, y + 20);
		document.layers[0].visibility = "SHOW";
	}
	else if(document.all)
	{
		x = event.clientX;
		y = event.clientY;
		document.all("lay").innerHTML = helpmsg;
		document.all["lay"].style.pixelLeft = x+10;
		document.all["lay"].style.pixelTop = y+20;
		document.all["lay"].style.visibility = "visible";
	}
}

function hide()
{
	if(document.layers)
	{
		document.layers[0].visibility = "HIDE";
	}
	else if(document.all)
	{
		document.all["lay"].style.visibility = "hidden";
	}
}

if(document.layers)
{
	document.write('<LAYER visibility="hide" bgcolor="#ffc"></LAYER>');
}
else if(document.all)
{
	document.write('<DIV id="lay" style="color:#000;border:2px solid #886;position:absolute;background-color:#ffc"></DIV>');
}

hide();

//-->
</script>
long;

mapping HI_TABLE_16 = 	
([
30		:	"<font color=999999>",
31		:	"<font color=ff0000>",
32		:	"<font color=00ff00>",
33		:	"<font color=ffff00>",
34		:	"<font color=0000ff>",
35		:	"<font color=ff00ff>",
36		:	"<font color=99ffff>",
37		:	"<font color=ffffff>",
]);

mapping LO_TABLE_16 =
([
30		:	"<font color=999999>",
31		:	"<font color=991111>",
32		:	"<font color=119911>",
33		:	"<font color=999911>",
34		:	"<font color=111199>",
35		:	"<font color=991199>",
36		:	"<font color=009999>",
37		:	"<font color=999999>",	
]);

mapping ANSI_TO_16;

string translate_to_html(string content)
{
	// 替代字元
	content = replace_string(content, "  ", "&nbsp;&nbsp;&nbsp;&nbsp;");
	content = replace_string(content,"□","█");
	content = replace_string(content,"Γ","Ｔ");
	content = replace_string(content,"ω","ｗ");
	content = replace_string(content, "\n", "<br>\n");

	foreach(string color, string b16 in ANSI_TO_16)
		content = replace_string(content, color, b16);
	
	content = remove_ansi(content);
	
	return content;
}

string replace_lt_gt(string content)
{
	content = replace_string(content, ">", " &gt; ");
	content = replace_string(content, "<", " &lt; ");
	
	return content;
}

void make_html(string content, mapping index)
{
	string text;
	string bgcolor = index["bgcolor"] || "white";
	int fontsize = index["fontsize"] || 12;
	string fontface = index["fontface"] || "新宋體";
	string filename = index["filename"] || "/www/tmp.html";
	string title = index["title"] || "無標題";
	int refresh = index["refresh"];
	

	text = bgcolor == "black" ? BLACK_HEADER : WHITE_HEADER;

	
	text += "<div style='font-size:"+fontsize+"px;font-family:"+fontface+";'><nobr>";
	text += translate_to_html(content);
	text += "</div>";
	text += bgcolor == "black" ? BLACK_FOOTER : WHITE_FOOTER;
	text += JAVA_SCRIPT;
	text = terminal_colour(text, ([
		"TITLE"		:	title,
		"REFRESH"	:	refresh?("<meta http-equiv='refresh' content='"+refresh+"'; url='"+filename+"'>"):"",
		"UPDATETIME"	:	TIME_D->replace_ctime(time()),
		"YEAR"		:	TIME_D->query_realtime_array()[YEAR]+"",
	]));
	write_file(filename, text, 1);
}

int mudlist_sort(mapping mudlist, string mud1, string mud2)
{
        string mud1_chinese = mudlist[mud1]["MUD_CHINESE_NAME"];
        string mud2_chinese = mudlist[mud2]["MUD_CHINESE_NAME"];
        string mud1_english = mudlist[mud1]["MUD_ENGLISH_NAME"];
        string mud2_english = mudlist[mud2]["MUD_ENGLISH_NAME"];

        if( sizeof(mud1_chinese) != sizeof(mud2_chinese) )
                return sizeof(mud1_chinese) > sizeof(mud2_chinese) ? 1 : -1;
        
        return strcmp(mud1_chinese || mud1_english, mud2_chinese || mud2_english);
}

void create_mudlist_html()
{
        string ipport;
        string ip;
        string cname;
        string ename;
        int i = 0;
        int port;
        int status;
        int users;
        string lasttime;
        mapping muds;
        mapping data;
        string *mudnamesort;
        string str;
        string msg;
        string text;
        
        muds = MUDLIST_D->query_mudlist();
        
        text  = "<DIV style='BORDER-BOTTOM: #aaa 3px double; WIDTH: 200px; COLOR: #333; FONT-SIZE: 16px'><IMG src='muds/mudlist/subtitle.gif'>中文泥巴列表</DIV><BR>";
        text += "<P>　以下列出目前大陸大部份已知的泥巴 <ACRONYM title=泥巴遊戲>MUD</ACRONYM>"; 
        text += "的即時列表，並偵測連線狀況與線上玩家人數供各位參考，若您想推薦某個中文泥巴站台，請用Zmud登錄遊戲 muds.cn 5000 與 Lonely 聯繫。</P>";
        text += "<UL><LI class=level1><DIV class=li>若您的網頁瀏覽器支持 JavaScript ，按欄位可依選擇排序。</DIV>";
        text += "<LI class=level1><DIV class=li>上線人數 N/A 為系統無從得知此間 <ACRONYM title=泥巴遊戲>MUD</ACRONYM> 之人數。</DIV></LI></UL><P>";
        text += "<SCRIPT language=javascript type=text/javascript src='muds/mudlist/sorttable.js'></SCRIPT></P><P>";
        
        text += "<TABLE style='BORDER-BOTTOM: #aaa 3px double; BORDER-LEFT: #aaa 3px double; PADDING-BOTTOM: 3px; PADDING-LEFT: 3px; WIDTH: 100%; PADDING-RIGHT: 3px; FONT-SIZE: 13px; BORDER-TOP: #aaa 3px double; BORDER-RIGHT: #aaa 3px double; PADDING-TOP: 3px' border=0 cellSpacing=0 cellPadding=0>";
        text += "<TBODY><TR><TD><TABLE width='100%'><TBODY><TR><TD width='50%'>目前共有" +sizeof(muds)+ "個泥巴</TD><TD width='50%' align=right>最近更新時間："+TIME_D->replace_ctime(time())+"</TD></TR></TBODY></TABLE>";
        text += "<TABLE style='WIDTH: 100%; FONT-SIZE: 13px; BORDER-TOP: #555 1px solid' id=mudlist class=sortable border=0 cellSpacing=0>";
        text += "<TBODY><TR>";
        text += "<TD style='BORDER-BOTTOM: #555 1px solid; PADDING-BOTTOM: 3px; PADDING-LEFT: 3px; PADDING-RIGHT: 3px; PADDING-TOP: 3px' bgColor=#efefdf>泥巴名稱</TD>";
        text += "<TD style='BORDER-BOTTOM: #555 1px solid; PADDING-BOTTOM: 3px; PADDING-LEFT: 3px; PADDING-RIGHT: 3px; PADDING-TOP: 3px' bgColor=#efefdf>網絡位置</TD>";
        text += "<TD style='BORDER-BOTTOM: #555 1px solid; PADDING-BOTTOM: 3px; PADDING-LEFT: 3px; PADDING-RIGHT: 3px; PADDING-TOP: 3px' bgColor=#efefdf align=center>連接埠</TD>";
        text += "<TD style='BORDER-BOTTOM: #555 1px solid; PADDING-BOTTOM: 3px; PADDING-LEFT: 3px; PADDING-RIGHT: 3px; PADDING-TOP: 3px' bgColor=#efefdf align=center>目前狀態</TD>";
        text += "<TD style='BORDER-BOTTOM: #555 1px solid; PADDING-BOTTOM: 3px; PADDING-LEFT: 3px; PADDING-RIGHT: 3px; PADDING-TOP: 3px' bgColor=#efefdf align=center>線上人數</TD>";
        text += "<TD style='BORDER-BOTTOM: #555 1px solid; PADDING-BOTTOM: 3px; PADDING-LEFT: 3px; PADDING-RIGHT: 3px; PADDING-TOP: 3px' bgColor=#efefdf align=center>最後接觸時間</TD></TR>"; 
        
        mudnamesort = sort_array(keys(muds)-({0}), (: mudlist_sort($(muds), $1, $2) :)) ;
        foreach(ipport in mudnamesort)
        {
                data  = muds[ipport];

                if( !stringp(ipport) || !mapp(data) ) continue;
                
                sscanf(ipport, "%s %d", ip, port);
                
                if( data["CONNECT_FAILED_TIMES"] > 0 )
                        status = 0;
                else
                        status = 1;
                
                if( data["USERS"] > 0 )
                        users = data["USERS"];
                else if( !data["USERS_COUNT_PARSE"] )
                        users = -1;
                else
                        users = 0;

                if( data["LAST_CONTACT_TIME"] )
                        lasttime = TIME_D->replace_ctime(data["LAST_CONTACT_TIME"]);
                else
                        lasttime = "";
                
                cname = data["MUD_CHINESE_NAME"]||"--未知名稱--";
                ename = data["MUD_ENGLISH_NAME"]||"--Unknown--";
                
                i++;
                if( i % 2) str = "bgColor=#ffffef";
                else       str = "bgColor=#efefdf";
                
                msg  = "<TR><TD style='BORDER-BOTTOM: #fff 1px solid; PADDING-BOTTOM: 3px; PADDING-LEFT: 3px; PADDING-RIGHT: 3px; PADDING-TOP: 3px' "+str+">";
                msg += "<A href='http://www.muds.cn/muds/mudlist/"+ip+"_"+port+"/"+ip+"_"+port+".html' target=_blank><FONT color=#000000>"+cname+"</FONT><BR><FONT color=#999999>"+ename+"</FONT></A></TD>";
                msg += "<TD style='BORDER-BOTTOM: #fff 1px solid; FONT-SIZE: 15px' "+str+">";
                msg += "<A href='telnet://"+ip+":"+port+"/'><FONT color=#000000>"+ip+"</FONT></A></TD>";
                msg += "<TD style='BORDER-BOTTOM: #fff 1px solid' "+str+" align=center>"+port+"</TD>";
                msg += "<TD style='BORDER-BOTTOM: #fff 1px solid; "+(status?"COLOR: #5f5' bgColor=#005f00":"COLOR: #f55' bgColor=#5f0000")+" align=center>"+(status?"○":"╳")+"</TD>";
                msg += "<TD style='BORDER-BOTTOM: #fff 1px solid' "+str+" align=center>"+(users<0?"<FONT color=#aaaaaa>N/A</FONT>":users)+"</TD>";
                msg += "<TD style='BORDER-BOTTOM: #fff 1px solid' "+str+" align=center>"+lasttime+"</TD></TR>";
                
                text += msg;
        }
        text += "</TBODY></TABLE></TD></TR></TBODY></TABLE></P><!-- SECTION [1-3357] -->";

        text += "<A name=中文泥巴玩家分佈狀況></A>";
        text += "<DIV style='BORDER-BOTTOM: #aaa 3px double; WIDTH: 200px; COLOR: #333; FONT-SIZE: 16px'><IMG src='muds/mudlist/subtitle.gif'>中文泥巴玩家分佈狀況</DIV><BR>";
        text += "<P><CENTER><IMG src='muds/mudlist/chart.png'></CENTER>";
            
        text += "<P></P><!-- SECTION [3358-4159] --><A name=中文泥巴玩家即時統計></A>";
        text += "<DIV style='BORDER-BOTTOM: #aaa 3px double; WIDTH: 200px; COLOR: #333; FONT-SIZE: 16px'><IMG src='muds/mudlist/subtitle.gif'>中文泥巴玩家即時統計</DIV><BR>";
        text += "<P><CENTER><A href='http://www.muds.cn/muds/mudlist/0_total_count/0_total_count.html' target=_blank><IMG border=0 src='muds/mudlist/0_total_count/0_total_count-day.png'> </A></CENTER>";
        text += "<P></P><!-- SECTION [4160-] --></TD></TR>";
    
        make_html(text, (["filename":"/www/mudlist.html", "title":"中文泥巴列表", "fontsize":15, "fontface":"宋體"]));
}

void create_html()
{
        create_mudlist_html();
}
	
void create()
{
	int fcolor, bcolor;
	
	ANSI_TO_16 = allocate_mapping(0);

	ANSI_TO_16[ESC+"[0m"] = "<font color=999999>";
	ANSI_TO_16[ESC+"[m"] = "<font color=999999>";

	for(fcolor=30;fcolor<=37;fcolor++)
	{
		ANSI_TO_16[ESC+"["+fcolor+"m"] = LO_TABLE_16[fcolor];
		ANSI_TO_16[ESC+"[0;"+fcolor+"m"] = LO_TABLE_16[fcolor];
		ANSI_TO_16[ESC+"[1;"+fcolor+"m"] = HI_TABLE_16[fcolor];
		ANSI_TO_16[ESC+"["+fcolor+";1m"] = LO_TABLE_16[fcolor];
	
		for(bcolor=41;bcolor<=47;bcolor++)
		{
			ANSI_TO_16[ESC+"["+fcolor+";"+bcolor+"m"] = HI_TABLE_16[fcolor];
			ANSI_TO_16[ESC+"["+bcolor+";"+fcolor+"m"] = HI_TABLE_16[fcolor];

			ANSI_TO_16[ESC+"[0;"+fcolor+";"+bcolor+"m"] = LO_TABLE_16[fcolor];
			ANSI_TO_16[ESC+"[0;"+bcolor+";"+fcolor+"m"] = LO_TABLE_16[fcolor];
			
			ANSI_TO_16[ESC+"[1;"+fcolor+";"+bcolor+"m"] = HI_TABLE_16[fcolor];
			ANSI_TO_16[ESC+"[1;"+bcolor+";"+fcolor+"m"] = HI_TABLE_16[fcolor];
			
			ANSI_TO_16[ESC+"["+fcolor+";1;"+bcolor+"m"] = HI_TABLE_16[fcolor];
			ANSI_TO_16[ESC+"["+bcolor+";1;"+fcolor+"m"] = HI_TABLE_16[fcolor];
			
			ANSI_TO_16[ESC+"["+fcolor+";"+bcolor+";1m"] = HI_TABLE_16[fcolor];
			ANSI_TO_16[ESC+"["+bcolor+";"+fcolor+";1m"] = HI_TABLE_16[fcolor];
		}
	}
	
	create_html();
}

string query_name()
{
	return "HTML 系統(HTML_D)";
}
