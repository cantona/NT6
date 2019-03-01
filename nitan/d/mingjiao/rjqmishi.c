//RJQMISHI.C

inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
這裡是一間秘室，石壁之上嵌入兩盞油燈，火苗幽藍，石室地板
用精鋼鑄就，中央有一巨大鐵爐，似乎也與地板鑄為一體。爐中火苗
熊熊，烈炎沖天。幾個壯士正在打造什麼兵器，地上的打鐵聲就是從
這裡傳出的。石室角落中有一扇小鐵門(men)。
LONG );
        set("exits", ([
                "south" : __DIR__"rjqjiguan",
                "down"  : __DIR__"rjqmenlou1",
        ]));
        set("no_clean_up", 0);
//        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}