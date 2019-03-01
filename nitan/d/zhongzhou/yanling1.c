inherit ROOM;
void create()
{
          set ("short", "延陵西路");
          set ("long", @LONG
這裡就是延陵東路，是中州的一條老街。兩邊的房屋看上
去已經很陳舊了。街道上冷冷清清的，偶爾一兩個人路過。再
往前走，就能隱隱的看見中州的西城樓了。路北面有間雜貨舖
開在這偏僻的地方，估計生意不會太好。
LONG);

        set("outdoors", "zhongzhou");

          set("exits", ([  
                    "west" : __DIR__"yanling2",
                    "north" : __DIR__"zahuopu",
                    "east"  : __DIR__"yanling",
        ]));
        set("objects",([
                __DIR__"npc/fushang":1,
                __DIR__"npc/poorman":1,
        ]));
       
        set("coor/x", -9060);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}