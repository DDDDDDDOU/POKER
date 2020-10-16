import { shallowMount, createLocalVue, mount } from "@vue/test-utils";
import ElementUI from "element-ui";
import personalcard from "../../src/components/personalcard";
const localVue = createLocalVue();
localVue.use(ElementUI);
/**
 * mock的axios
 * 可以根据需要添加其他函数功能
 */
const axios = {
    get: async () => "success",
    post:async ()=>"success"
};
const getBase64=jest.fn();
describe("init",()=>{
    const wrapper = shallowMount(personalcard, {
        mocks: {
            axios,
            getBase64
        },
        localVue
    });

    it("data",()=>{
        expect(wrapper.vm.update_flag).toEqual(false);
        expect(wrapper.vm.user).toEqual({
            id: '123',
            name: '交通大学',
            birthday: '1896-04-07',
            sex: -1,
            reg_time: '2020-07-01',
            phone: '021134200000',
            userMongo: {
                avatar: ''
            }
        }
        );
    });

    it('function',()=>{
        //getFile

        expect(wrapper.vm.getFile({name:'123'})).toEqual(true);
        //cancel
        expect(wrapper.vm.cancel()).toEqual(true);
        //upload
        expect(wrapper.vm.upload()).resolves.toBeTruthy();
    })

})




