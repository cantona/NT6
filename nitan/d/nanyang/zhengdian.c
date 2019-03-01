// Room: /d/nanyang/zhengdian.c
// Last Modified by winder on Nov. 20 2001

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",RED "正殿" NOR);
        set("long",@LONG
正殿面闊三間，青石為牆，黑瓦覆頂，顯出一派簡樸的風格，殿內
正中供著一尊諸葛武侯彩像，手握羽扇，微捻胡須，神態端然自如；兩
側牆壁上題著不少詩篇詞賦，大都筆法剛勁，揮毫洒脫，顯然是出自一
些胸懷大志的壯男兒之手。
LONG);
        set("exits",([
                "south" : __DIR__"wuhouci",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6930);
	set("coor/y", 800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}