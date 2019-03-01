#include <combat.h>
#include <ansi.h>
inherit ROOM;
string *all_dirs = ({"north","south","east","west","southwest","northeast","southeast","northwest"});
void create()
{
        set("short", "雪原");
        set("long",
"這裡是一片無垠的雪地，天地之間一片蒼茫，兩行足跡遠遠地延伸出\n"
"去，似乎永無盡頭。此時狂風大作，風中隱隱傳來厲嘯和“咯咯”的笑聲。\n"
);
        set("no_magic", "1");

        set("exits", ([ /* sizeof() == 2 */
          "north" : __FILE__,
          "south" : __FILE__,
          "east" : __FILE__,
          "west" : __FILE__,
          "southeast" : __FILE__,
          "southwest" : __FILE__,
          "northeast" : __FILE__,
        "northwest" : __FILE__,
        ]));

        set("objects", ([
                //      __DIR__"npc/roc" : 1,
                ])
        );
        setup();
}

int valid_leave(object ob,string dir)
{
        object roc;

        switch(random(15))
        {
                case 1:
                case 2:
                case 3:
                        message_vision(RED"\n狂風飛雪之中，似乎有什麼東西自你上一掠而過！"NOR,ob);
                        roc = new("/d/llszhuang/npc/roc");
                        roc->move(environment(ob));
                        COMBAT_D->do_attack(roc,ob,query_temp("weapon", roc),TYPE_QUICK);
                      message_vision(YEL"幽冥大鵬振羽長嘯，身形轉眼消失在雲層中。\n\n"NOR,ob);
                        destruct(roc);
                        return 1;
                default:
                        if( dir == all_dirs[random(4)] )
                                addn_temp("doom_trigger", 1, ob);
                        if( dir == all_dirs[4+random(4)] )
                                addn_temp("doom_trigger", -1, ob);

                        if( query_temp("doom_trigger", ob) == 3 )
                        {
                     message("channel:chat", YEL"【江湖故事】江湖傳言："+ob->name()+"在某一天突然闖入了柳綠山莊。\n"NOR,users());
                                ob->move(__DIR__"gate");
                                delete_temp("doom_trigger", ob);
                                return notify_fail("你終于找到了出口，來到了綠柳山莊的正門。\n");
                        }


                        if( query_temp("doom_trigger", ob) == -3 )
                        {
                                write("你終于找到了來時的路，渡過了小河，循原路回。\n");
                                ob->move(__DIR__"dukou");
                                delete_temp("doom_trigger", ob);
                              return notify_fail("你終于找到了來時的路，渡過了小河，循原路回到了渡口。\n");
                        }

                        return 1;
        }

}
