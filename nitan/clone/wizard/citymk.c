
/*
 * 物件： 城市精靈(City Maker) V1.0
 * 作者： 冰河 (Glacier@［雪域．黑潮］)
 * 日期： 2001/01/11
 * 備註： ES_Base_Code
 * 修改： 功能模塊修改成嚮導方式，加入地圖檔錯誤判斷。
 *        任何時候輸入點 "."，都可以放棄編輯。
 *                            Glacier -- 2001.2.20
 *
 * 修改： 加入自己設定文件名功能。文件名導出格式為：城市名_房間名.c
 *        其中城市名為地圖文件的名稱，房間名在地圖文件第一行設定。
 *                            Lonely -- 2001.3.12 
 */
#pragma save_binary
inherit ITEM;
inherit F_AUTOLOAD;

#include <mudlib.h>
//#define _check_map
#define _show_map

mixed maps, icons, icons1;
mapping room_short = ([]),room_filename = ([]);
string city,current_path;
string *outdoors_room;
string outdoors;
int _Mrow, _Mcol, _size;
int set_path(string arg);
int set_outdoors_room(string arg);
int save_file(string yn, string file_name, string file);
int confirm_make(string yn);
void create()
{
        set_name("城市精靈 V1.1", ({ "citymaker", "maker" }) );
        set_weight(2000);
        set("unit", "個" );
        set("long", @LONG
    這個是一個方便巫師工作的工具，可以快速建立完整的區域結構。
請使用 help citymaker 獲得詳細幫助。
LONG
        );
        setup();
}

void init()
{
        if( wizardp(environment()) ) {
                seteuid(getuid(environment()));
                add_action("do_makecity", "make");
                add_action("do_help", "help");
        }
}

int process_map(string file)
{
        string input,*line;
        int i,j,v;
        int _Trow, _Tcol;
        if(file_size(file)>0)
        {
            input=read_file(file);
//處理 line
            line=explode(input,"\n");
            icons1=explode(line[0]," ");
            for(i=0;i<sizeof(icons1);i++)
            {
                j=i+1;
                if (strsrch(icons1[i],"\t")!=-1 || strsrch(icons1[i],".")==-1)
                {
                write("[ Citymaker ]：房間標識位錯誤，請檢查地圖第一行標識位[ "+ j +" == "+icons1[i]+" ]處。\n");
                write("[ Citymaker ]：含有製表符或者<房間標識.房間名稱>之間不含分割符\".\"。\n");
                return 0;
                }            
            }
            icons=allocate(sizeof(icons1));
            for(i=0;i<sizeof(icons1);i++)
            {
                //icons[i]=allocate(2);
                icons[i]=allocate(3);
                icons[i]=explode(icons1[i],".");
            }
            for(i=0;i<sizeof(icons1);i++)
            {
                room_short[icons[i][0]] = icons[i][1];
                room_filename[icons[i][0]] = icons[i][2];
            }
//處理 mapping room_short
            _Trow=sizeof(line);
            _Mrow=_Trow-1;
            _size=_Trow;
            for(i=1;i<(sizeof(line));i++)
            {
                _Tcol=sizeof(line[i]);
                if (_Mcol<_Tcol) {_Mcol=_Tcol;}
            }
            if (_size<_Mcol) {_size=_Mcol;}
//處理成矩陣
            for(i=1;i<(sizeof(line));i++)
            {
                j=i+1;
                if (strsrch(line[i],"\t")!=-1)
                {
                write("[ Citymaker ]：房間標識位錯誤，請檢查地圖第["+j+"]行[ "+line[i]+" ]處。\n");
                write("[ Citymaker ]：含有製表符。\n");
                return 0;
                }               
                for (_Tcol=sizeof(line[i]);_Tcol<_Mcol;_Tcol++)
                 {
                        line[i]+= " " ;
                 }
            }
                maps = allocate(_size);
//處理 maps
                for(v=1;v<(sizeof(line));v++)
            {
            maps[v-1]=allocate(_size);
            maps[v-1]=explode(line[v],"");
            }
            return 1;
        } else return 0;
}



int makeroom(int _row, int _col)
{
        int i;
        string file_name,file,*exit_key,room;
        mapping exit=([]);
        room=maps[_row][_col];
                write("[ Citymaker ]：room("+_row+","+_col+") == "+room+" ");
  if (_row>1)                       {if (maps[_row-1][_col] == "|"   && maps[_row-2][_col]!=" ")     {exit["north"]=room_filename[maps[_row-2][_col]];}}
  if (_row>1 && _col<_Mcol-1)       {if (maps[_row-1][_col+1] == "/" && maps[_row-2][_col+2]!=" ")   {exit["northeast"]=room_filename[maps[_row-2][_col+2]];}}
  if (_col<_Mcol-1)                 {if (maps[_row][_col+1] == "-"   && maps[_row][_col+2]!=" ")     {exit["east"]=room_filename[maps[_row][_col+2]];}}
  if (_row<_Mrow-1 && _col<_Mcol-1) {if (maps[_row+1][_col+1] == "\\"&& maps[_row+2][_col+2]!=" ")   {exit["southeast"]=room_filename[maps[_row+2][_col+2]];}}
  if (_row<_Mrow-1)                 {if (maps[_row+1][_col] == "|"   && maps[_row+2][_col]!=" ")     {exit["south"]=room_filename[maps[_row+2][_col]];}}
  if (_row<_Mrow-1 && _col>1)       {if (maps[_row+1][_col-1] == "/" && maps[_row+2][_col-2]!=" ")   {exit["southwest"]=room_filename[maps[_row+2][_col-2]];}}
  if (_col>1)                       {if (maps[_row][_col-1] == "-"   && maps[_row][_col-2]!=" ")      {exit["west"]=room_filename[maps[_row][_col-2]];}}
  if (_row>1 && _col>1)             {if (maps[_row-1][_col-1] == "\\"&& maps[_row-2][_col-2]!=" ")   {exit["northwest"]=room_filename[maps[_row-2][_col-2]];}}
  //file_name=current_path++"_"+room_filename[maps[_row][_col]]+".c";
  file_name=current_path+room_filename[maps[_row][_col]]+".c";
  file=sprintf("/*\n * 文件    : %s (%s)\n",room_short[maps[_row][_col]],room_filename[maps[_row][_col]]);
        file+=sprintf(" * 作者    : %s(%s@%s)\n * 創建    : %s\n",this_player()->query("name"),this_player()->query("id"),MUD_NAME,ctime(time()));
        file+=@FILE_HEAD
 * 工具    : Build with Citymaker@Glacier
 * 修改    : Changed By Lonely@泥潭
 */
#include <ansi.h>
inherit ROOM;
void create()
{
FILE_HEAD
;
        file+=sprintf("\tset(\"short\", \"%s\");\n",room_short[maps[_row][_col]]);
file+=@FILE_LONG
        set("long", @LONG
夜.泊.秦.淮.居.誰.家？

LONG
);
        set("objects",([
        ]));
        set("exits",([
FILE_LONG;
;
        exit_key=keys(exit);
        for(i=0;i<sizeof(exit_key);i++) {
                file=sprintf("%s\t\"%s\" : __DIR__\"%s\",\n",file,exit_key[i],exit[exit_key[i]]);
        }
        file+=@FILE_2
        ]));
FILE_2
;
  if (member_array(lower_case(maps[_row][_col]),outdoors_room)==-1 )
{
        file+=@FILE_3
        setup();
//      replace_program(ROOM);
}
FILE_3
;
}
else {
        file+=sprintf("\tset(\"outdoors\",\"%s\");\n",city);
        file+=@FILE_3
        setup();
//      replace_program(ROOM);
}
FILE_3
;
}

return save_file("y", file_name, file);
}

int do_makecity(string arg)
{
        int _row,_col;
        string file,room;
        if (!arg) return notify_fail ("[ Citymaker ]：makecity <地圖檔案名>\n");
        if (strsrch(arg,".")!=-1 || strsrch(arg," ")!=-1) 
        {
        write("[ Citymaker ]：錯誤地圖檔名，地圖檔中不允許出現\".\"或者\" \"，\n ");
        write("              請直接使用你想建立的城市名為地圖檔名。\n");
        return 1;
        }
        else
        {
        
                //city=;
                file=resolve_path(this_player()->query("cwd"), arg);
                if(process_map(file))
                {
                        write("[ Citymaker ]：正在載入地圖檔[ "+file+" ]...\n");
#ifdef _check_map
                        for(_row=0;_row<sizeof(maps);_row++)
                        {
                                for(_col=0;_col<sizeof(maps[_row]);_col++)
                                {
                                room=maps[_row][_col];
                                write("room("+_row+","+_col+") == "+room + "\n");
                                }
                        }
#endif
#ifdef _show_map
                        for(_row=0;_row<sizeof(maps);_row++)
                        {
                                for(_col=0;_col<sizeof(maps[_row]);_col++)
                                {
                                room=maps[_row][_col];
                                write(""+room + "");
                                }
                         write("\n");
                        }
                        write("[ Citymaker ]：_Mrow = "+_Mrow+" _Mcol = "+_Mcol+"\n");
#endif
                        write("[ Citymaker ]：地圖檔[ "+file+" ]載入完成!!\n");
                }
                else
                {
                        return notify_fail("[ Citymaker ]：地圖檔[ "+file+" ]載入失敗。\n");
                }
        }       
          write("[ Citymaker ]：請設定存儲檔案目錄(默認為當前目錄)：");
          input_to ( "set_path" );

        return 1;
}

int save_file(string yn, string file_name, string file)
{
        if( strlen(yn)<1 || yn[0]!='y' ) return 1;
        
      if(file_name[0..2]!="/u/") return 0;
//只允許在/u/目錄下面建立文件
        rm(file_name);
        write(" 建立 " + file_name + "....");
        
        if( write_file(file_name, file,1)==1 ) {
                write("OK!\n");
                return 1;
        } else
                write("你沒有寫入這個檔案(" + file_name + ")的權利。\n");
                return 0;
}

int set_path(string arg)
{
        string dir;
        if (arg == ".") { write ("[ Citymaker ]：放棄本次操作。\n"); return 1; }
        if (strsrch(arg," ")!=-1) 
        {
        write("[ Citymaker ]：錯誤的路徑，請設定存儲檔案目錄(默認為當前目錄)：");
        input_to ( "set_path" );        
        return 1;
        }
        if(!arg)
        {
                if(dir = this_player()->query("cwd"))
                {
                        current_path=dir;
                        write("[ Citymaker ]：自動設定存儲檔案目錄為當前目錄[ "+current_path+" ]。\n");
                        write("[ Citymaker ]：請設定户外房間類型(例如：c,g 則地圖為 c、g 的房間將被設定為户外)：");
                        input_to("set_outdoors_room");
                        return 1;
                } else return notify_fail("[ Citymaker ]：無法自動設定目錄，放棄操作。\n");
        }
        else
        {
                dir = resolve_path(this_player()->query("cwd"), arg);
                if(file_size(dir)!=-2) { write("[ Citymaker ]：沒有這個目錄，放棄操作。\n"); return 1; }                 
                if(dir[strlen(dir)-1]!='/') dir += "/";
                current_path=dir;
                write("[ Citymaker ]：設定存儲檔案目錄為[ "+current_path+" ]。\n");
                write("[ Citymaker ]：請設定户外房間類型(例如：c,g 則地圖為 c、g 的房間將被設定為户外)：");
                input_to("set_outdoors_room");                
        }
                return 1;        
}
int set_outdoors_room(string arg)
{
        int  i;
        string *tmp,test,argt;
        argt=lower_case(arg);
        if (arg == ".") { write ("[ Citymaker ]：放棄本次操作。\n"); return 1; }     
        if (strsrch(argt," ")!=-1 )
        {
        write("[ Citymaker ]：户外房間類型設定錯誤，不允許出現\" \"。\n");
        write("[ Citymaker ]：請設定户外房間類型(例如：c,g 則地圖為 c、g 的房間將被設定為户外)：");      
        input_to ( "set_outdoors_room" );       
        return 1;
        }
        tmp=(explode(lower_case(arg),","));
        for (i=0;i<sizeof(tmp);i++)
        {
        test=tmp[i];
        if (strlen(test)>1) {
                write("[ Citymaker ]：户外房間設定錯誤，房間標識長度應為單個字符。\n");
                write("[ Citymaker ]：請設定户外房間類型(例如：c,g 則地圖為 c、g 的房間將被設定為户外)：");
                input_to ( "set_outdoors_room" );       
                return 1;               
                }
        }
        if(!arg) 
        {
        write ("[ Citymaker ]：設定所有房間為户外...OK。\n");
        }
        outdoors_room=(explode(lower_case(arg),","));
        for (i=0;i<sizeof(outdoors_room);i++)
        {
        outdoors=outdoors_room[i];
        write("[ Citymaker ]：設定房間[ "+outdoors+" ]為户外...OK。\n");
        }
        write("[ Citymaker ]：設定完成，Citymaker 將會生成城市檔案，請確認(y/n)：");
        input_to("confirm_make");   
        return 1;
}
int confirm_make(string arg)
{
        int  _row,_col;
        int count=0;
        if( arg=="" ) 
        {
        write("[ Citymaker ]：需要確認，您確定嗎(y/n)？");
        input_to("confirm_make");
        return 1;
        }       
        if( arg[0]!='y' && arg[0]!='Y' ) {write ("[ Citymaker ]：放棄本次操作。\n"); return 1;}
        write("[ Citymaker ]：正在建立城市 ... ...\n");    
        for(_row=0;_row<sizeof(maps);_row++)
        {
        for(_col=0;_col<sizeof(maps[_row]);_col++)
        {
                if (maps[_row][_col]!=" "
                 && maps[_row][_col]!="|"
                 && maps[_row][_col]!="/"
                 && maps[_row][_col]!="\\"
                 && maps[_row][_col]!="-" )
                {
                        makeroom(_row,_col);
                        count++;
                }
                }
        }
        write("[ Citymaker ]：操作報告，共計[ " + count +" ]個房間！\n");   
        return 1;
}

int do_help(string arg)
{
        if(arg=="citymaker" ||arg== "maker")
        {
                write(@HELP_LONG
城市精靈 V1.1 ( 2001.2)            - By Glacier@［雪域．黑潮］
                                     Email:wizard@game.com.cn
                                     
這個是一個為方便巫師工作的城市工具，可以快速建立完整的區域結構。

1.編輯地圖檔, 範例如下：
-----------------------------------------------------------------
a.客房.kefang b.廂房.xiangfang c.走廊.zoulang d.大廳.dating
e.廚房.chufang f.花園.huayuan g.大門.damen h.內室.neishi
(注意：上兩行應合併為一行，由於過寬，為了便於顯示，所以在這裏分為兩行)
  g   b
  |  / \
b-c-b   b
  |  \ /
a-d-a b
  |
h-f-e
------------------------------------------------------------------
地圖説明：   本地圖檔所加邊框(---)，為解釋地圖所用，實際地圖中沒有。
             地圖第一行為圖例，採用<房間標識.房間名稱.房間文件名>的
             方式，即a代表客房，地圖中所有a均被處理成客房。 房間標
             識、房間名稱和房間文件名之間用＂.＂分割。
             用＂-、\、/、|＂來表示常用的的八中通路(不考慮地形)即：
             west、east、northwest、southeast、northeast、southwest
             north、south。
注意事項：   所有房間均應在第一行有圖例説明，否則將無法正常生成房間。
             地圖中所有字符均為半角字符，只允許出現空格＂ ＂，不允許
             出現製表符 \t 。為避免出錯請嚴格按造本地圖檔建立。
2. 指令格式：make <地圖檔>  ( 最好把城市名作為地圖檔名稱， 這是因為
             Citymaker 在設置outdoors房間的時候使用地圖檔名作為房間
             的所屬城市。)
3. Citymaker 需要設定存放檔案的路徑： <目錄名> (默認為當前所在目錄)。
4. Citymaker 需要設定户外的房間：<户外房間標識,户外房間標識,...
             所設定的房間將被設定為户外(默認為室內)。       
5. 如果以上設定無誤，確認後 Citymaker 會批量生成城市檔案。(確認後本
             序將直接改寫重名文件，所以請注意你所者設置的存儲目錄。
6. 本程序歡迎修改，但請保留原作者名。       

HELP_LONG);
                return 1;
        }
        return 0;
}

string query_autoload() { return "";}

void autoload(string param)
{return ;}

