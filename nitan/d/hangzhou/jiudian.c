//Cracked by Roath
// /d/hangzhou/jiudian.c   牛家村酒店
// by maco 99/12/22

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{        set("short", "酒店");
        set("long", @LONG
這是座單門獨戶的小酒店，檐下擺著兩張板桌，桌上罩著厚厚一
層灰塵，東首擺了個碗櫥。小酒店的主人是個跛子，可以向他打酒(f
ill)。店中似乎也沒什麼菜色，無非是些蠶豆、花生等下酒之物。
LONG );

         set("exits", ([ /* sizeof() == 2 */
                   "west" : __DIR__"village",  
                 ])
         );

         set("objects", ([
                CLASS_D("taohua") + "/qusan" : 1  
         ]));

         set("cost", 1);
         set("outdoors", "hangzhou");

         set("coor/x", 3890);
        set("coor/y", -1800);
        set("coor/z", 0);
        setup();
}
void init()
{
        add_action("do_fill", "fill");
}
int do_fill(string arg)
{
        object ob, obj, me = this_player();

        if (!objectp(obj = present("qu san", environment(me))))
        {        write("掌櫃的不在！\n");
                return 1;
        }

        if (!living(obj)){
                write("你還是等掌櫃的醒過來再說吧。\n");
                return 1;
        }

        if( !arg || !(ob=present(arg,this_player())) || !query("liquid", ob)){
                write("你要把酒裝在哪兒？\n");
                return 1;
        }

        switch (MONEY_D->player_pay(this_player(), 20)) {
        case 0: {
                write("窮光蛋，一邊呆著去！\n");
                return 1;
                }
        case 2: {
                write("您的零錢不夠了，銀票又沒人找得開。\n");
                return 1;
                }
        }

        if( query("liquid/remaining", ob) )
                message_vision("$N將"+ob->name()+"裡剩下的"+query("liquid/name", ob)+
                "倒掉。\n", this_player());
        message_vision("$N給曲三二十文銅板。\n曲三給$N的"+ob->name()+"裝滿燒酒。\n", this_player());

        if( this_player()->is_fighting() ) this_player()->start_busy(2);

        set("liquid/type", "alcohol", ob);
        set("liquid/name", "燒酒", ob);
        set("liquid/remaining", query("max_liquid"), ob);
        set("liquid/drink_func", 0, ob);
        set("liquid/drunk_apply", 4, ob);
        return 1;
}