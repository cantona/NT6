// This program is a part of NITAN MudLIB
// Jitan3.c

#include <ansi.h>
inherit ROOM;

void start_worship(object who, int n);

void create()
{
        set("short", "衡山祭壇");
        set("long", @LONG
五嶽之南嶽衡山祭壇處，祭壇上有青銅鼎香爐一座，終年香火不滅，
若身有閻王契，點上召神香，則可召喚「衡山府君」出現。。
LONG );
        set("exits", ([
                "down" : "/d/henshan/wangyuetai",
        ]));
        set("objects", ([
                __DIR__"obj/xianglu" : 1,
        ]));
        set("outdoors", "henshan");
        set("worship", 3);        
        setup();
}

void init()
{
        add_action("do_put", "put");
}

int do_put(string arg)
{
        object me, ob, obj, env;
        string what, where;
        int n;
        
        me = this_player();
        env = environment(me);
        if( !objectp(ob = present("xiang lu", env)) )
                return 0;    
                
        if( !arg || sscanf(arg, "%s in %s", what, where) != 2)
                return 0;       
                
        if( where == "xiang lu" ) {
                if( what != "magic xiang" ) {
                        tell_object(me, "青銅鼎香爐裏可不能亂扔東西！\n");
                        return 1;
                }  
                             
                if( !objectp(obj = present(what, me)) &&
                    !objectp(obj = present(what, env)) ) {
                        tell_object(me, "你身上和附近沒有這樣東西啊。\n");
                        return 1;
                }

                if( present("henshan fujun", this_object()) ) {
                        tell_object(me, "衡山府君已經在你面前了，你就沒有這個必要了吧。\n");
                        return 1;
                }
                                        
                message_vision( MAG "$N" MAG "將召神香插進銅鼎香爐裏，淡淡的香味瀰漫着四周。\n" NOR, me);
                obj->move(ob);
                set("no_get", 1, obj);
                obj->start_borrowing();  
                n=query("worship", env);
                if ( n ) start_worship(me, n);
                return 1;
        }
        return 0;
}

void start_worship(object who, int n)
{
        object ob;

        if( !objectp( ob = present("contract", who) ) ||
            query("owner", ob) != query("id", who) )
                return;
        
        ob = new("/d/reborn/npc/fujun" + n);
        set("worship",query("id",  who), ob);
        ob->move(this_object());
        ob->start_borrowing(); 
        ob->command("say 「何方來人，斗膽呼喚本君現身？」");
}