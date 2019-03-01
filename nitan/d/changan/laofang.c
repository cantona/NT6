//Room: laofang.c

inherit ROOM;

void create ()
{
        set ("short", "牢房");
        set("long", @LONG
這是一間牢房，室內昏暗無光，只有借著一碗口大的小洞射進來
的余光，才使人視力模糊的依稀見物。西邊角落裡堆放著一些已經腐
爛的稻草，室內並不暗潮，甚至還有一張簡陋的舊床，牢門是用一根
根手臂粗的鐵棍做成的，中間有許多的空隙，室外的光線可以射進來。
LONG );
        set("exits", ([
        ]));

        setup();
}