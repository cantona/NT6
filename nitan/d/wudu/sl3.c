inherit ROOM;

void create()
{
        set("short", "鬆樹林");
        set("long", @LONG
這裡是一片濃密的鬆樹林，前面已經沒有了道路，你必須不時砍
斷橫在你面前的枝椏。林內光線黑暗，靜的能讓你聽到自己的心跳聲，
只有你踩在地上厚厚的鬆針和枯枝上發出的沙沙聲。前面依稀透著一
點光亮，你不由長長的吁了一口氣。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "west" : __DIR__"sl2",
                "south" : __DIR__"sl5",
        ]));

        setup();
        replace_program(ROOM);
}
