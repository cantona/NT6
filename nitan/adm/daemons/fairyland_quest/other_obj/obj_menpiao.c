//                標準描述長度示例                                   |
// 遊戲內門票
// by naihe  2002-11-03  于茂名

inherit ITEM;

int query_autoload() { return 1; }

void create()
{
    set_name("『幻境﹒遙遠傳說之起緣﹒幽靈顯現』 的門票", ({"men piao","piao"}));
    set_weight(10);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "這是一張“幻境”遊戲的入場門票，憑它你可以入場遊戲一次。\n");
        set("unit", "張");
        set("value", 1);
        set("hjmenpiao", 1);
    }

    setup();
}
