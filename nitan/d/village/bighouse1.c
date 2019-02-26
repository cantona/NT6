// Room: /d/village/bighouse1.c

inherit ROOM;

void create()
{
        set("short", "前廳");
        set("long", @LONG
這是一間很普通的青磚瓦房，但在這個小村子裏已是首屈一指的
『豪宅』了。這裏是前廳，廳裏的擺設很簡單，鄉下土財主都很財迷，
就算有幾個錢兒，也是捨不得花。東邊是個小門通向內室。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "west" :__DIR__"sroad4",
            "east" :__DIR__"bighouse2",
        ]));

        setup();
        replace_program(ROOM);
}
 