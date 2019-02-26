// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "碎石小路"); 
        set("long", @LONG
這條碎石小路東邊是一個梨園，西首便是富貴如意廳，路上生滿
了青苔，一不當心就會跌倒，兩側不知名的野花開得倒也茂盛，淡淡
的散發着一種清新的花香。草窠中偶爾傳來一兩聲蟋蟀的叫聲。一抬
頭，可以看見幾個或是蜈蚣狀，或是老鷹狀的風箏高高飛舞在藍天白
雲中。
LONG );
        set("outdoors", "wansong");
        set("type","road");
        set("exits",([
                "east":__DIR__"liyuan",
                "west":__DIR__"fuguitin",
        ]) );
        set("objects" , ([
                __DIR__"obj/flower" : 1,
        ]));
        set("coor/x",-580);
        set("coor/y",220);
        set("coor/z",80);
        setup();
}
/*
int valid_leave(object me, string dir)
{
    if (!wizardp(this_player()) && (dir=="west" || dir=="east"))
         {
           if( query("kar", random(this_player()))<2 )
              {
               message_vision("$N一腳踩在青苔上, 不小心滑了一跤, 四腳朝天地摔在地上起不來。\n\n\n", this_player());
               this_player()->unconcious();
              return 0;
              }
           else return 1;
         }
     else return 1;
}
 */     
