// Code of ShenZhou
// Room: didao.c 地道入口
// Zhangchi 3/00

inherit ROOM;

void create()
{
        set("short", "地道入口");
        set("long", @LONG
這裏是厚土旗挖的地道入口，一座小土堆的後面，是一個黑漆漆
的洞穴通往地下。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "down": "/d/mingjiao/didao/didao1",
                "east" : "/d/mingjiao/tohtq5",
]));
        
        set("cost", 1);

        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if( (!query("family", me) || query("family/family_name", me) != "明教") && 
                dir == "down")
                return notify_fail("幾名厚土旗壯漢擋住你，説道：外人不得進入地道！\n");
        
        return ::valid_leave(me,dir);
}