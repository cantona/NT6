// shulele by 2001/9/24

#define SOS_DIR       "/data/sos/"
#define SOS_FILENAME  "sos"

#include <ansi.h>

inherit F_SAVE;

mapping *notes;

string query_save_file()
{
	return SOS_DIR + SOS_FILENAME ;
}

void done_post(object me, mapping note, string text)
{
    int i; 

	if (strlen(text) < 20) return;
    note["msg"] = text;
    i = sizeof(notes);
    for( ; i > 0; i-- ) 
        if( notes[i-1]["author"] == me->query("id") ) break;
    if( !pointerp(notes) || i > 0 )
        if(!sizeof(notes)) notes = ({ note });
        else {
            notes[i-1]["title"] = note["title"];
            notes[i-1]["author"] = note["author"];
            notes[i-1]["msg"] = note["msg"];
            notes[i-1]["time"] = note["time"];
            notes[i-1]["solve"] = "";
        }
    else
        notes += ({ note });
    tell_object(me, HIM "求救OK。請等待。\n");
 // tell_object(me, HIM "巫師正忙著，請等待。\n");
 // tell_object(me, HIM "你先做你自己的事情吧，一會用sos read看看是否解決了，ｏｋ？\n" NOR);
	message("channel:wiz", HIY "【求救】：玩家 "+note["author"]+" 使用"BLINK" SOS "NOR HIY"緊急求救，請在線巫師使用 sos 命令查看。\n" NOR,users());
    save();
    return;
}

void list_bug(object me)
{
    int i;
    string str,s;
    if (sizeof(notes)<1) {
        write("沒人發出 sos 求救信號。\n");
        return;
    } 
    s = sprintf("玩家已經發出的 sos 列表如下:\n"
                "----------------------------------------------------------------------\n");
    for( i = 0; i<sizeof(notes); i++){
        str = sprintf("%d) %-50s %10s %s \n",
                           i+1, notes[i]["title"], notes[i]["solve"]==""?"No solved":"By "+notes[i]["solve"],
                           ctime(notes[i]["time"])[0..9] );
        s = s + str;
    }
    me->start_more(s);                
}

void do_read(object me, int i) 
{
    string s;
    if( i > sizeof(notes) || i < 1) {
        write("無此編號!!\n");
        return;
    }
    s = sprintf("%d) %-50s %10s %s\n"
              "----------------------------------------------------------------------\n"
              "%s",
               i, notes[i-1]["title"], notes[i-1]["solve"]==""?"No solved":"By "+notes[i-1]["solve"],
               ctime(notes[i-1]["time"])[0..9], notes[i-1]["msg"] );
    me->start_more(s);
}

int search_id(string id)
{
    int i;
    if( !(i = sizeof(notes)) ) return 0;
    for( ; i > 0; i-- ) 
        if( notes[i-1]["author"] == id ) break;
    return i;
}

int do_solve(object me, int i)
{
    if( i > sizeof(notes) || i < 1) {
        write("無此編號!!\n");
        return 0;
    } 
    if ( notes[i-1]["solve"]!="" ) {
        write(notes[i-1]["solve"]+"已經標志啦!\n");
        return 1;
    }
    notes[i-1]["solve"] = me->query("id");
    save();
    write("該 sos 信息已標志為解決。\n");
    return 1;
}

int main(object me, string arg)
{
    mapping note;
    object where;
    string s, str,arg1; //line 40
    int i,arg2;
    restore();
    if (!arg) {
        if(!wiz_level(me)){
            tell_object(me, HIM "你現在是在" HIY MUD_NAME HIM "裡，你可以向在線WIZ求救。\n" NOR);
      //    tell_object(me, HIM "趕快向巫師們發出求救：ＳＯＳ！\n" NOR);
                       where = environment(me);
            if (!where) 
                s=sprintf("%s(%s)求救",
			(string)me->name(),
			(string)me->query("id"));
            else
                s=sprintf("%s(%s)在%s求救",
			(string)me->name(),
			(string)me->query("id"),
			(string)where->query("short"));
            note = allocate_mapping(5);
            note["title"] = s;
            note["author"] = me->query("id"); 
            note["time"] = time();
            note["solve"] = "";
            me->edit( (: done_post, me, note :) );
        }
        else {
            list_bug(me);
        }
        return 1;
    } 

    if( sscanf(arg, "%s %s", s, arg1) == 2 ) {
        if( !wiz_level(me) ) return notify_fail("格式不對，具體使用方法請參閱 help sos \n");
        if ( s != "solve" ) return notify_fail("格式不對，具體使用方法請參閱 help sos \n");
        if ( arg1 =="all" ) {
           if( !(i = sizeof(notes)) ) return notify_fail("沒人發出sos求救信號。\n");
           for( ; i > 0; i-- ) 
               notes[i-1]["solve"] = me->query("id");
           write("所有的 sos 信息已經標志為解決了。\n");
           return 1;
        }
        i = search_id(arg1);
        if( i > 0 ) { 
            do_solve( me, i );
            return 1;
        }
    }
    if( sscanf(arg, "%s %d", s, arg2) == 2 ) {
        if( !wiz_level(me) ) return notify_fail("格式不對，具體使用方法請參閱 help sos \n");
        if ( s != "solve" ) return notify_fail("格式不對，具體使用方法請參閱 help sos \n");
        do_solve( me, arg2 ); 
        return 1;
    }
    if ( sscanf(arg, "%s", s) == 1 ) 
    switch(arg){
        case "read":       
            if( !(i = sizeof(notes)) )
                return notify_fail("還沒有人做過 sos 呼叫！\n");
            else {
                i = search_id( me->query("id") );
                do_read(me,i);
            }
            break;
        case "list":
            if( !wiz_level(me) ) return notify_fail("格式不對，具體使用方法請參閱 help sos \n");
            list_bug(me);
            break;
        case "pack":
            if( !wiz_level(me) ) return notify_fail("格式不對，具體使用方法請參閱 help sos \n");
            if( !(i = sizeof(notes)) ) return notify_fail("沒人發出 sos 求救信號。\n");
            for( ; i > 0; i-- ) 
                if( "" != notes[i-1]["solve"] ) {
                    printf("%s的 sos 求救已被刪除！\n", notes[i-1]["author"]);
                    if( sizeof(notes) == 1 ) notes = ({});
                    else if(i==1) notes = notes[1..sizeof(notes)-1];
                    else if( i == sizeof(notes) ) notes = notes[0..sizeof(notes)-2];
                    else notes = notes = notes[0..i-2] + notes[i..sizeof(notes)-1];
                }
            save();
            break;
        case "solve":
            if( !wiz_level(me) ) return notify_fail("格式不對，具體使用方法請參閱 help sos \n");
            return notify_fail("格式: sos solve <編號或玩家id>\n");
            break;
        default:
            if( !wiz_level(me) ) return notify_fail("格式不對，具體使用方法請參閱 help sos \n");
            if( sscanf(arg, "%d", i) == 1 )
                do_read( me, i );
            else if( sscanf( arg, "%s", str ) == 1 ) {
                i = search_id(str);
                if( i == 0 ) return notify_fail("無此玩家發出的 sos 信息！\n");
                do_read( me, i );
            }
    }
    else return notify_fail("格式不對，具體使用方法請參閱 help sos \n");
    return 1;
}

int help(object me)
{
	if (!wiz_level(me) )
	write(@HELP
指令格式 : 
           sos
           sos read
這個指令可以在系統出現bug時來向巫師求助。
輸入該命令後，系統將提示你輸入對 bug 的描述。玩家在這裡應該將 bug
出現的情況和系統的提示盡量詳細地進行說明，以便巫師修改該 bug。
每個玩家只能貼一條 sos，新的 sos 將覆蓋以前的輸入。
可以用 sos read 閱讀自己貼出的 sos。
HELP
    );
	else 
write(@HELP
指令格式 : 
           sos
           sos <號碼或玩家id>
           sos list
           sos pack
           sos solve <號碼或玩家id>
這個指令可以輔助巫師處理玩家提出的 bug 列表。sos 和 sos list 的功能一樣，
都是將所有的 bug 信息進行列表。帶參數的 sos 命令，根據參數的不同，將顯示
對應號碼或對應玩家的 bug 的詳細信息。sos solve用來標志某個bug已經被解決了。
sos pack 將刪除所有已經標志為解決了的 bug。
HELP
    );
    return 1;
}
