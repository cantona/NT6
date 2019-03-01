// xuanya.c
inherit ROOM;
void create()
{
        set("short","懸崖");
        set("long", @LONG
這是華山上懸崖上的一片平台，地勢險惡。平台旁便是萬丈深淵，
低頭望下，只見一天雲海。華山弟子多在此練劍打坐，借天時地勢，
勤練武功。平時華山掌門也在此指點及考教門下弟子。
LONG );
        set("exits",([
                "west" : __DIR__"houyuan",
        ]));
        set("outdoors", "huashan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
 