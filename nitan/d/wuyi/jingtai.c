// Room: /d/wuyi/jingtai.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "鏡台");
        set("long", @LONG
這裡緊靠二曲之南，黝黑的巖壁上大書“鏡台”二字，便是九天上
仙女來此沐浴後梳妝的鏡台了。鏡台與玉女峰相對，遠遠望去，便如玉
女臨鏡插花的形態。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northwest" : __DIR__"yunvfeng",
                "south"     : __DIR__"huxiaoyan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1390);
        set("coor/y", -5020);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
