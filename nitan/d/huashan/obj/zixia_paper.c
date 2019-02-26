//Cracked by Kafei
// zixia_paper.c
inherit ITEM;

void create()
{
        set_name("紙箋", ({"zixia paper", "zixia"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "頁");

                set("long",
"紫霞千變，萬氣歸宗。紫氤正氣，相輔相承。聚龍虎，暢筋脈。開玄關，\n"
"過重樓。通任督，就玄功。功成者氣精具增，洗骨淨髓。動靜由心，動者\n"
"如脱兔，靜者若處子。冰心觀萬象，天塌亦不驚。根骨得天後，百病皆難\n"
"侵。一舉一動，勁隨意到，勁到力至，無堅不摧也。\n"
"行功者須在華山小築密室內閉關，行功法則如下：\n"
"。。。。。\n"
"。。。。。。。\n"
"biguan <臂力> <悟性> <根骨> <身法>\n"
"備註：所增各項天賦值的總和為四點。\n"
"例如：biguan 2 0 1 1， 臂力加二，悟性不變。根骨身法俱增一點。\n");

                set("value", 10000000);
                set("material", "paper");
//                set("no_drop","這樣東西不能離開你。\n");
        }
}