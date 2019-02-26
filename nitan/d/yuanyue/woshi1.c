inherit ROOM;
void create()
{
        set("short", "燕子塢"); 
        set("long", @LONG
這裏是金獅的卧室。平常金獅倒算是豪爽，但一回到這裏，便古
古怪怪的，大門緊閉，連窗户都會關上，銀龍好幾次想進來，都被金
獅轟了出去，弄得銀龍好生沒趣，一怒之下，趁金獅出門，在屋裏還
算雪白的牆上留下了金獅的彌足珍貴的題詞『燕子塢』。屋子裏其實
除了張牀外，什麼也沒有。銀龍費盡心思，也沒發現有什麼不可告人
的地方。
LONG );
        set("type","indoors");
        set("exits",([
                "west":__DIR__"grass4",
                "south":__DIR__"grass3",
        ]) );

        set("item_desc", ([
                "牆": "牆上面龍飛鳳舞寫了幾個大字：\n銀龍到燕子塢一遊，哈哈！可惜啥好玩的沒有。\n",
                "wall": "牆上面龍飛鳳舞寫了幾個大字：\n銀龍到燕子塢一遊，哈哈！可惜啥好玩的沒有。\n",
        ]) ); 
        set("coor/x",-580);
        set("coor/y",250);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}    
