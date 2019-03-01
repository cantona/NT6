// neiyuan.c
inherit ROOM;

void create()
{
        set("short", "內院");
        set("long", @LONG
這裡是梅莊的內院，從這裡走過去就可以找到四位莊主，這裡似
乎非常安靜，可以聽見落葉觸地的聲音，但又似乎非常吵鬧，經常可
以聽到嘈雜的琴聲，但這琴聲又可以將你的心弦打亂，你真不知道該
怎麼形容這個地方。有一位壯年的漢子，腰懸寶劍守在院門口。
LONG );
        set("outdoors", "meizhuang");
        set("exits", ([ /* sizeof() == 2 */
            "south" : __DIR__"senlin1",
            "north" : __DIR__"zoulang1",
        ]));
        set("objects", ([ /* sizeof() == 1 */
            __DIR__"npc/huyuan.c" : 1,
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
