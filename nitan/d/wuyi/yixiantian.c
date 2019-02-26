// Room: /d/wuyi/yunwo.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "一線天");
        set("long", @LONG
一線天原名靈巖，位於二曲之南。因巖壁縱裂一線，天光如絲，而
得今名。南壁峭崖下，三洞森然。入洞後，頓覺陰氣森森，暑氣全消。
仰窺丹崖，如鬼斧神工，數十丈一線青天，彎曲如虹。相傳此處為伏羲
上古因悲天憫人，手掄玉斧劈開的。巖壁上數以千計的白蝙蝠，也是人
間罕見的奇觀。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"path6",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1390);
        set("coor/y", -5050);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
