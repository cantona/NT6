inherit ROOM;

void create()
{
        set("short", "昆侖山麓");
        set("long", @LONG
    四下無聲，只有風吹鬆濤，幽韻天成，仰視蒼天，注視群山，令
人不覺愴然而發思古之幽情！往前看，只見一道飛巖，下臨絕崖，往
下看，峭壁如刀削，雲卷霧湧，深不見底。
LONG );
        set("no_new_clean_up", 0);
        set("outdoors", "kunlun");

        set("exits", ([ /* sizeof() == 3 */
                "northeast" : __DIR__"kunlun1",
                "up" : __DIR__"kunlun3",
        ]));

        setup();
        replace_program(ROOM);
}