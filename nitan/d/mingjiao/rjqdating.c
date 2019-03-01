//RJQTING.C

inherit ROOM;

void create()
{
        set("short", "銳金旗大廳");
        set("long", @LONG
這是銳金旗的大廳，雖然都是練武之人，這裡卻布置得古色古香，
顯出銳金旗的與眾不同。大廳正面高懸一塊牌匾，上書四個燙金大字
『銳氣金風』，一百二十年前，明教與來犯的蒙古軍隊一場鏖戰，銳
金旗力守玄天崖，死者八、九，教主親書此匾以勵教眾，銳金旗以此
為五旗之首。廳中央擺有茶幾，銳金旗掌旗使莊錚正襟而坐，正在讀
一本書卷。
LONG );
        set("exits", ([
                "south" : __DIR__"rjqyuan",
        ]));

        set("objects",([
                __DIR__"npc/zhuangzheng":1,
        ]));
        setup();
        replace_program(ROOM);
}