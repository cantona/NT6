inherit ROOM;

void create()
{
        set("short", "鬆樹林");
        set("long", @LONG
這裡是一片濃密的鬆樹林，前面已經沒有了道路，你必須不時砍
斷橫在你面前的枝椏。不遠處一株千年的古鬆直插雲霄，它下面縱橫
交錯的樹根似乎在向人訴說它悠久的歲月。林內光線黑暗，靜的能聽
到你自己的心跳聲，只有你踩在地上厚厚的鬆針和枯枝上發出的沙沙
聲。前面依稀透著一絲光亮，你不由高興的緊走幾步。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "north" : __DIR__"sl5",
                "west" : __DIR__"sl7",
        ]));

        setup();
        replace_program(ROOM);
}