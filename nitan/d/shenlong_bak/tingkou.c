// /d/shenlong/datingkou 大廳口
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
inherit ROOM;
string* npcs = ({
        __DIR__"npc/boy",
        __DIR__"npc/boy2",
        __DIR__"npc/boy3",
        __DIR__"npc/boy4",
        __DIR__"npc/girl",
});

void create()
{
        set("short", "大廳口");
        set("long", @LONG
這是大廳的門口，向內可進入神龍教的大廳，門口站著許多神龍教
的教徒，全副武裝，警惕地注視四周，從廳內依稀傳來一個渾厚的聲音，
似乎裡面正在召開什麼重要會議。
LONG
        );
        set("valid_startroom",1);
        set("outdoors", "shenlong");
        set("exits", ([
                "west"  : __DIR__"changlang",
                "enter" : __DIR__"dating",
        ]));
        set("objects", ([
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                CLASS_D("shenlong") + "/first" : 1,
        ]));
        setup();
        "/clone/board/shenlong_b"->foo();
}

int valid_leave(object me, string dir)
{
        mapping myfam=query("family", me);
        object *inv;
        int haveguarder;

        if( !(query("sg/spy", me) || 
                query("family/family_name", me) == "神龍教") && 
                dir == "enter" )
        {
                inv = all_inventory(this_object());
                for(int i = 0; i < sizeof(inv); i++ )
                        if( query("family/family_name", inv[i]) == "神龍教" || 
                                query("sg/spy", inv[i]) )
                        {
                                 haveguarder++;
                                 if( living(inv[i]) ) inv[i]->kill_ob(me);
                        }
                if( haveguarder > 0 )
                        return notify_fail("你也太目中無人了吧，這兒還有人守著呢。\n");
         }

         return ::valid_leave(me, dir);
}
