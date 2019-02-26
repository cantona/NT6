#include <ansi.h>

#define BOOK_DIR "/clone/lonely/book/"
int get_book();

nosave mixed *story = ({
        "少林英雄大會後，姑蘇燕子塢",
        "慕容復：段譽這小子太可恨了！居然這樣羞辱我！",
        "鄧百川：可是他的六脈神劍實在厲害呀！",
        "包不同：非也非也，我慕容家的參合指並不輸於六脈神劍。",
        "慕容復：事到如今，只能強行修煉參合指了！",
        "公冶乾：可是公子，聽説修煉參合指所需的八種指法祕籍已流落江湖，不知在何人之手。",
        "風波惡：無妨，明日我四人就出莊尋找，誓為公子取得祕籍！",
        (: get_book :),
        "數日後",
});

string *books = ({
        "lianhuazhi",
        "qixingzhi",
        "tianlongzhi",
        "qilian",
        "youmingzhi",
        "tianzhuzhi",
        "duoluoyezhi",
        "xiuluozhi",
        });

string *finder = ({"鄧百川", "包不同", "公冶乾", "風波惡"});

string prompt() { return HIW "【武林軼事】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int get_book()
{
        object ob, book, owner;
        int i = sizeof(books);
        string temp, *find_book = ({});

        while(i--) {
                ob = find_object(BOOK_DIR + books[i]);
                if(objectp(ob)) {
                        find_book += ({ob->name()});
                        if(objectp(environment(ob)) && userp(environment(ob))) {
                                owner = environment(ob);
                                tell_object(owner, "你突然被感到後腦一痛，好像被硬物打了一下。\n");
                                owner->unconcious();
                        }
                        destruct(ob);
                                }
        }
        if (! i = sizeof(find_book)) {
                story += ({finder[random(sizeof(finder))] + "：公子，屬下無能，在江湖上浪蕩這麼久也沒有為你找到一本祕笈。"});
                story += ({"慕容復：這不怪你，因為我已經收集到修煉所有祕笈了。"});
        } else {
                temp = find_book[--i];
                if(i) {
                        while(--i) temp += "、" + find_book[i];
                        temp += "及" + find_book[0];
                }
                story += ({finder[random(4)] + "：公子，我找到了" + temp + "，你看！"});
                story += ({"慕容復：太好了，看來我練成參合指有望了。"});
        }
        return 1;
}