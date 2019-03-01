// room-ji.c 草棚

inherit ROOM;

void create()
{
        set("short", "草棚");
        set("long", @LONG
這是在部族東北部孤零零的一座草棚。這棚屋土牆草頂，形式宛如內
地漢人的磚屋，只是甚為簡陋，旁邊有一個小水漕。你悄悄的掩向小屋後
面，正想探頭從窗子向屋內張望，那知窗內有一張臉同時探了上來。望北
去就是大戈壁了。
LONG
        );
        set("exits", ([
            "enter" : __DIR__"room-ji1",
            "south" : __DIR__"road2",
           "northwest" : __DIR__"gebi1",
            "southeast" : __DIR__"caoyuan6",
        ]));

        set("outdoors", "hasake");

        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
       if( dir == "northwest" && !userp(me))
            return notify_fail("...\n");  
      
       return ::valid_leave(me,dir);
}