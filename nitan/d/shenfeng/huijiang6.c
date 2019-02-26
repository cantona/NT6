inherit ROOM;

void create()
{
        set("short", "草棚");
        set("long", @LONG
這裏是小山腳下，孤令令的有一座草棚。這棚屋土牆草頂
形式宛如內地漢人的磚屋，只是甚為簡陋。只見小屋之後系著
匹高頭白馬，健腿長鬣。你悄悄的掩向小屋後面，正想探頭從
窗子向屋內張望，那知窗內有一張臉同時探了上來。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                    "north" : __DIR__"huijiang3",
        ]));
        set("objects", ([
                __DIR__"npc/ji"  : 1,
        ]) );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}