// Room: /d/wuyi/yingzuiyan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "鷹嘴巖");
        set("long", @LONG
“雄鷹獨立健無倫，鋭喙昂頭實逼真”。鷹嘴巖是一座渾然一體的
巨巖，光禿禿的巖頂，東端向前突出，尖曲如喙，宛如一隻展翅欲飛、
搏擊長空的雄鷹。相傳，這是一隻非禮仙女的魔鷹，天帝在降伏它的時
候，連它的下顎也被閃電削掉了。如今，曾經沸騰的鮮血也被無情的歲
月風化成一道道痛苦的裂痕，生命在這裏停泊成蒼老的歸宿。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"path12",
                "north"     : __DIR__"path13",
                "southeast" : __DIR__"path14",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1400);
        set("coor/y", -4920);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
