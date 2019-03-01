#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "太湖");
        set("long", @LONG
綠衫少女臉帶微笑，如春花般嬌痴無瑕。兩手劃槳，不時採摘蓮
實戲耍。口中漫聲唱道：  "菡萏香連十頃陂，小姑貪戲採蓮遲。晚來
弄水船頭灘，笑脫紅裙裹鴨兒。" 碧玉般湖面淡淡彌散著輕柔的曲調。
LONG );
        set("outdoors", "yanziwu");
        setup();
        replace_program(ROOM);
}
