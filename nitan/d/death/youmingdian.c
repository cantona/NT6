// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;

void create ()
{
        set("short", HIB "幽冥殿" NOR   );
        set("long", HIB @LONG
這裏便是名聞天下，令人提起心驚膽寒的閻幽冥殿。人死後都會在
這裏受到應有的處置。正前一張大桌。正前坐着十殿閻羅。

LONG NOR);
        set("exits", ([ /* sizeof() == 1 */
                "south" : __DIR__"youmingjie",
                "north" : __DIR__"yanluodian",
        ]));
        
        set("hell", 1);
        set("no_fight", 1);
        
        set("objects", ([ /* sizeof() == 2 */
                __DIR__"npc/yanluo"        : 1,
/*
                __DIR__"npc/yinchangsheng" : 1,
                __DIR__"npc/wangfangping"  : 1,                
*/
        ]));
        set("no_magic", 1);
        setup();

}

int valid_leave(object me, string dir)
{
        int i;
        object ob;
        me = this_player();
        if (dir == "north")
        {
                if( !wizardp(me) && !query("hell_quest/鎖陽丹", me) && 
                    !query("over_quest/hell_quest/鎖陽丹", me) )
                        return notify_fail(CYN "十殿閻羅看了你一眼，喝道：你還不滾"
                                           "回去還陽，來這裏湊什麼熱鬧！\n" NOR);
        }
        return ::valid_leave(me, dir);
}
