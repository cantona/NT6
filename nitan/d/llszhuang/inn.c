inherit ROOM;
void create()
{
        set("short", "楓林小棧");
        set("long",
"這是楓林渡口旁邊的一個小酒家，破爛的酒旗在北風中飛舞。北面的\n"
"路通往曾經聲名顯赫一時的綠柳山莊。自從綠柳山莊的兇訊傳揚開去之後，\n"
"這裡就變得非常冷清了。只有要去綠柳山莊探明究竟的人才會在這裡喝點\n"
"酒，壯一壯膽，攢足精神。\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "north" : __DIR__"dukou",
          "southeast" : __DIR__"road2",
        ]));
        set("objects", ([
           // "/d/city/npc/xiaoer2" : 1,
        ]));
        setup();
}
