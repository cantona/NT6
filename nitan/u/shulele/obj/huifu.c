#include <ansi.h>
inherit ITEM;

void create()
{
set_name("往生石",({"wangsheng shi","sheng shi","shi","stone"}));
set("unit","塊");
setup();
}

int query_autoload()
{
return 1;
}

void init()
{
add_action("do_hf","huifu");
}

int do_hf(string id)
{
string arg1,arg2;       
object me = this_player();
if ( !id || !wizardp(me) )
        return 0;
if ( file_size(sprintf("/data/login/%c/%s.o",id[0],id))>0 )
        write(id+"的上線檔案已經存在，取消此步驟，繼續下一步。\n");
else if ( file_size(sprintf("/backup/2013-6-24/login/%c/%s.o",id[0],id))<=0 )
        {
        write(id+"的上線檔案備份目錄中沒有，無法恢復。\n");
        return 1;
        }
else    {
        arg1 = sprintf("/backup/2006-7-6/login/%c/%s.o",id[0],id);     
        arg2 = sprintf("/data/login/%c/%s.o",id[0],id);
        if ( !("/cmds/adm/adcp.c")->main(me,arg1+" "+arg2) )
                return notify_fail(id+"上線記錄恢復失敗。\n");
        write(id+"上線記錄恢復完畢。\n");       
        }
        
if ( file_size(sprintf("/data/user/%c/%s.o",id[0],id))>0 )
        return notify_fail(id+"的檔案已經存在，請手動恢復。\n");
if ( file_size(sprintf("/data/user/%c/%s.oo.o",id[0],id))<=0 )
        return notify_fail(id+"的檔案備份目錄中沒有，無法恢復。\n");
arg1 = sprintf("/data/user/%c/%s.oo.o",id[0],id);
arg2 = sprintf("/data/user/%c/%s.o",id[0],id);
if ( !("/cmds/adm/adcp.c")->main(me,arg1+" "+arg2) )
        return notify_fail(id+"記錄恢復失敗。\n");
write(id+"記錄恢復完畢。\n");
message("shout",HIR"【"BLK"系統"NOR HIR"】"BLK"數據恢復："+id+" 數據恢復完畢。\n"NOR,users());
return 1;
}
