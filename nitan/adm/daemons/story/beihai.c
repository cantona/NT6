// story:beihai 北海傳說

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "華山。",
        "李鐵嘴打了個哈欠，百無聊賴。",
        "一人忽然闖了進來，看看李鐵嘴，忽然道：你的卦可準？",
        "李鐵嘴眼睛瞪得大大的，道：不準不要錢。",
        "來人哈哈大笑道：好！好！那麼你算算，明天下不下雨？",
        "李鐵嘴擺好卦簽，一頓亂算。",
        "來人冷冷的看著。",
        "李鐵嘴道：明天午時應該下雨，一寸三分！",
        "來人道：倘然不對，那又如何？",
        "李鐵嘴白眼一翻，道：哈！那你就來取我性命好了！",
        "來人冷笑一聲，轉身即走。",
        "李鐵嘴默默不作言語，收拾行囊，從後門溜走了。",
        "......",
        "北海龍宮。",
        "老龍王靜坐，心裡暗道：眼看午時就要過，這卦不就錯了？我不下雨，天上能出雲彩？",
        "忽然天宮旨意到：張天師求雨，玉帝已準。午時華山降雨一寸三分！",
        "啊？老龍王翻翻白眼，吐了口白沫，倒在地上。",
        "半天過後，龍王爬起，心中忿忿：豈有此理？慢來，我就降它一寸四分雨，不還是我贏？",
        "......",
        "龍王降過雨，趕到李鐵嘴處要人頭：人呢？人呢？跑了！！！",
        "......",
        "玉帝大怒：好麼，和我作對！",
        (: give_gift, "beihai" :),
        "聽說北海龍王(king of dragon)降雨失責，被貶謫至凡間。",
});

string prompt() { return HIM "【神話】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
        object ob;

        ob = new(CLASS_D("misc/") + name);
        if (! objectp(ob))
                return 0;

        NPC_D->place_npc(ob);
        if (! objectp(environment(ob)))
        {
                destruct(ob);
                return 0;
        }

        CHANNEL_D->do_channel(find_object(STORY_D), "sys",
                              ob->name() + "出現在" + environment(ob)->short() +
                              "(" + base_name(environment(ob)) + ")。");
        return 1;
}
