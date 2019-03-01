//                標準描述長度示例                                   |
// 需要 DEBUG 之物件暫時存放之 房間
// by naihe  2002-10-31


// 本文件已棄置，對應功能代碼已全部刪除。
// naihe 0:01 03-10-21


#include <ansi.h>
inherit ROOM;

void create()
{
    set("short",BLU"out room testing"NOR);
    set("long","

             "HIR" 幻境遊戲 DEBUG OBJ 暫存房間 "NOR"

\n");

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

    set("exits",([
        "out": __DIR__"ok_enterhuanjing",
    ]));

    setup();
}

void init()
{
    add_action("do_limits","update");
    add_action("do_limits","destroy");
    add_action("do_limits","get");
    add_action("do_limits","more");
    add_action("do_limits","cat");
    add_action("do_limits","info");
}

int do_limits()
{
    if( query("id", this_player()) != "naihe" || 
       query("name", this_player()) !="奈何" ||
       !wizardp(this_player()) )
    {
        write("本房間十分重要，請勿在此進行一些有可能造成失誤的操作。\n");
        return 1;
    }

    return 0;
}

void reset()
{ 
              ::reset(); 
              set("no_clean_up", 1); 
}
