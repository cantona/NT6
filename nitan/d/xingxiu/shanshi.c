// Room: /d/xingxiu/shanshi.c
// Last Modified by Winder on Apr. 25 2001

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "山石");
        set("long", @LONG
這裏是星宿海海邊一處山石。東面是方圓幾百裏都是一望無際的湖
泊和沼澤。因為陰冷潮濕，此處毒蟲繁殖甚富。星宿派弟子常來此捕捉
毒蟲，以備練毒之用。南邊有個黑黢黢的山洞(cave)。
LONG
        );
        set("objects", ([
                CLASS_D("xingxiu")+"/shihou" : 1,
                __DIR__"npc/haoshou"  : 1,
        ]) );
        set("exits", ([
                "eastdown" : __DIR__"xxhb4",
        ]));
        set("item_desc", ([
              "cave" : "山洞裏飄出一股股腥臭味，你還是快點離開吧。\n"
        ]) );
        set("coor/x", -50300);
        set("coor/y", 20400);
        set("coor/z", 200);
        set("outdoors", "xingxiuhai");
        setup();
}

void init()
{
        object me, ob;
        mapping fam;
        me = this_player();
        fam=query("family", me);
  
        if((objectp(present("lanyu bo", me)) ||
                objectp(present("shenmu wangding", me))) &&
                objectp(ob = present("shihou zi", environment(me))))
        {
                message_vision("$N對着$n大吼一聲：大膽"+RANK_D->query_rude(me)+"，竟敢偷拿本派寶物！\n", ob, me);   
                ob->kill_ob(me);
        }
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");   
}

int do_enter(string arg)
{
        object me;
        mapping myfam;
        me = this_player();
        myfam=query("family", me);

        if( !arg || arg=="" ) return 0;
        if (arg == "cave" )
        {
                if ((!myfam || myfam["family_name"] != "星宿派") &&
                        objectp(present("shihou zi", environment(me))))
                        return notify_fail("獅吼子閃身攔在你面前，喝道：不想捱揍的就快滾開！\n");
                message_vision("$N小心翼翼地往山洞裏探了探。\n", me); 
                message("vision",me->name() + "一彎腰往山洞裏鑽了進去。\n", environment(me), ({me}) );
                me->move(__DIR__"cave");
                message("vision",me->name() + "從外面鑽了進來。\n", environment(me), ({me}) );
                        return 1;
        }     
}

int valid_leave(object me, string dir)
{   
        if((objectp(present("lanyu bo", me)) ||
                objectp(present("shenmu wangding", me))) &&
                objectp(present("shihou zi", environment(me))) &&
                dir == "east")
                return notify_fail("獅吼子閃身攔在你面前，喝道：想溜？沒那麼容易！\n");
        
        return ::valid_leave(me, dir);
}
