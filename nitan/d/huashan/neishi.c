// Room: /d/huashan/neishi.c

inherit ROOM;

void create()
{
        set("short", "內室");
        set("long", @LONG
這裏有些昏暗，窗櫺上落了少許灰塵，看來平時並沒有人勤於打
掃。有一些劍宗弟子斜斜的靠在角落的牀上沉沉的睡着。
LONG );
        set("exits", ([ /* sizeof() == 4 */
             "west": __DIR__"xiaowu",
        ]));
        set("no_fight", 1);
        set("sleep_room", 1);

        setup();
        replace_program(ROOM);
}