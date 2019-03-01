inherit ROOM;
void create()
{
        set("short", "柳綠山莊");
        set("long",
"此時天色已暗，莊門裂開，只見這座破舊的莊院深邃闊大，不知至何\n"
"處終止。前面一條長長的甬道，已被白雪所覆蓋，一路通往莊院。\n"
);
        set("no_magic", "1");

        set("exits", ([ /* sizeof() == 2 */
          "north" : __DIR__"yongdao2",
          "south" : __DIR__"gate",
        ]));
        setup();
}
