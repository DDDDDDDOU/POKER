import { shallowMount, createLocalVue} from "@vue/test-utils";
import ElementUI from "element-ui";
import information from "../../src/components/information";


const localVue = createLocalVue();
localVue.use(ElementUI);

const axios = {
    get: async () => "success",
    post:async ()=> "success"


};
const generator=jest.fn();



describe("init",()=>{
    const wrapper = shallowMount(information, {
        mocks: {
            axios,
            generator
        },
        localVue
    });

    it("data",()=>{
        expect(wrapper.vm.basic_flag).toEqual(false);
        expect(wrapper.vm.contact_flag).toEqual(false);
        expect(wrapper.vm.sexStr).toEqual("未知");

        expect(wrapper.vm.user).toEqual({
            id: 0,
            name: '交通大学',
            birthday: '1896-04-07',
            sex: -1,
            type: 0,
            reg_time: '2020-07-01',
            email: 'se128@sjtu.edu.cn',
            phone: '021-34200000'
        }
        );
    })

    it('function',()=>{
        //sex
        expect(wrapper.vm.sex()).toEqual('未知');
        wrapper.setData({user:{
                id: 0,
                name: '交通大学',
                birthday: '1896-04-07',
                sex: '1',
                type: 0,
                reg_time: '2020-07-01',
                email: 'se128@sjtu.edu.cn',
                phone: '021-34200000'
            }})

        //sex
        expect(wrapper.vm.sex()).toEqual('男');
        wrapper.setData({user:{
                id: 0,
                name: '交通大学',
                birthday: '1896-04-07',
                sex: '0',
                type: 0,
                reg_time: '2020-07-01',
                email: 'se128@sjtu.edu.cn',
                phone: '021-34200000'
            }})

        //sex
        expect(wrapper.vm.sex()).toEqual('女');
        wrapper.setData({user:{
                id: 0,
                name: '交通大学',
                birthday: '1896-04-07',
                sex: '-1',
                type: 0,
                reg_time: '2020-07-01',
                email: 'se128@sjtu.edu.cn',
                phone: ''
            }})

        //sex
        expect(wrapper.vm.sex()).toEqual('未知');

        //sexStrToNum
        wrapper.setData({sexStr:'男'});
        expect(wrapper.vm.sexStrToNum()).toEqual(true);
        //sexStrToNum
        wrapper.setData({sexStr:'女'});
        expect(wrapper.vm.sexStrToNum()).toEqual(true);
        //sexStrToNum
        wrapper.setData({sexStr:'其他'});
        expect(wrapper.vm.sexStrToNum()).toEqual(false);

        //update
        wrapper.setData({birthright:'2020-07-24'});
        expect(wrapper.vm.update()).toEqual(false);
        //update
        wrapper.setData({birthright:'2006-07-24'});
        expect(wrapper.vm.update()).toEqual(false);
        wrapper.setData({user:{
                id: 0,
                name: '交通大学',
                birthday: '1896-04-07',
                sex: '-1',
                type: 0,
                reg_time: '2020-07-01',
                email: 'se128@sjtu.edu.cn',
                phone: '1879670152'
            }})
        expect(wrapper.vm.update()).toEqual(false);
        wrapper.setData({user:{
                id: 0,
                name: '交通大学',
                birthday: '1896-04-07',
                sex: '-1',
                type: 0,
                reg_time: '2020-07-01',
                email: 'se128@sjtu.edu.cn',
                phone: '18796700152'
            }})
        expect(wrapper.vm.update()).resolves.toBeTruthy();

        //basic
        wrapper.setData({
            basic_flag:true,
            errMessage: {
                name: {
                    message: "该用户重复或格式不正确",
                    flag: true
                },
                phone: {
                    message: "电话号码格式不正确或重复",
                    flag: false
                },

            },
        });
        expect(wrapper.vm.basic()).toEqual(false);
        //basic
        wrapper.setData({
            errMessage: {
                name: {
                    message: "该用户重复或格式不正确",
                    flag: false
                },
                phone: {
                    message: "电话号码格式不正确或重复",
                    flag: false
                },

            },
        });
        expect(wrapper.vm.basic()).toEqual(false);
        wrapper.setData({basic_flag:false});
        expect(wrapper.vm.basic()).toEqual(true);


        //contact
        wrapper.setData({
            contact_flag:true,
            errMessage: {
                name: {
                    message: "该用户重复或格式不正确",
                    flag: true
                },
                phone: {
                    message: "电话号码格式不正确或重复",
                    flag: false
                },

            },
        });
        expect(wrapper.vm.contact()).toEqual(false);
        wrapper.setData({
            contact_flag:true,
            errMessage: {
                name: {
                    message: "该用户重复或格式不正确",
                    flag: false
                },
                phone: {
                    message: "电话号码格式不正确或重复",
                    flag: false
                },

            },
        });
        expect(wrapper.vm.contact()).toEqual(false);

        wrapper.setData({
            contact_flag:false

        });
        expect(wrapper.vm.contact()).toEqual(true);




    })



})
//
// describe('function',()=>{
//     const wrapper = shallowMount(information, {
//         mocks: {
//             axios
//         },
//         localVue
//     });
//
//
//     it("func",()=>{
//
//         //sex()
//         wrapper.setData({
//             user:{
//                 id: null,
//                 name: null,
//                 birthday: '2002-03-03',
//                 sex: "1",
//                 reg_time: null,
//                 email: 'se128@sjtu.edu.cn',
//                 phone: null,
//                 userMongo: {
//
//                 }
//     }});
//         expect(wrapper.vm.sex()).toEqual("男");
//
//         wrapper.setData({
//             user:{
//                 id: null,
//                 name: null,
//                 birthday: '2002-03-03',
//                 sex: "0",
//                 reg_time: null,
//                 email: 'se128@sjtu.edu.cn',
//                 phone: null,
//                 userMongo: {
//
//                 }
//             }});
//         expect(wrapper.vm.sex()).toEqual("女");
//
//         wrapper.setData({
//             user:{
//                 id: null,
//                 name: null,
//                 birthday: "2002-03-03",
//                 sex: "3",
//                 reg_time: null,
//                 email: 'se128@sjtu.edu.cn',
//                 phone: null,
//                 userMongo: {
//
//                 }
//             }});
//         expect(wrapper.vm.sex()).toEqual("未知");
//
//     });
//
//     it("other",async ()=>{
//         //sexStrToNum()
//         wrapper.setData({
//             sexStr:"男"
//         })
//         expect(wrapper.vm.sexStrToNum()).toEqual(true);
//         expect(wrapper.vm.user.sex).toEqual("1");
//         wrapper.setData({
//             sexStr:"ayc"
//         })
//         expect(wrapper.vm.sexStrToNum()).toEqual(false);
//         expect(wrapper.vm.user.sex).toEqual("-1");
//
//         wrapper.setData({
//             sexStr:"女"
//         })
//         expect(wrapper.vm.sexStrToNum()).toEqual(true);
//         expect(wrapper.vm.user.sex).toEqual("0");
//
// //age()
//
//         wrapper.setData({
//             user:{
//                 id: null,
//                 name: null,
//                 birthday: "2002-03-03",
//                 sex: 0,
//                 reg_time: null,
//                 email: 'se128@sjtu.edu.cn',
//                 phone: null,
//                 userMongo: {
//                     avatar:null
//                 }
//             }});
//
//         // expect(wrapper.vm.user.birthday).toEqual( "2002-03-03");
//         // expect(wrapper.vm.age()).toEqual(18);
//
//
//
//         //basic()
//         expect(wrapper.vm.basic()).toEqual(true);
//         expect(wrapper.vm.basic_flag).toEqual(true);
//         expect(wrapper.vm.basic()).toEqual(false);
//         expect(wrapper.vm.basic_flag).toEqual(false);
//
//
//         //contact()
//         expect(wrapper.vm.contact()).toEqual(true);
//         expect(wrapper.vm.contact_flag).toEqual(true);
//         expect(wrapper.vm.contact()).toEqual(false);
//         expect(wrapper.vm.contact_flag).toEqual(false);
//
//         //sessionupdate()
//         expect(wrapper.vm.sessionUpdate()).toEqual(true);
//     })
//
// })
//
// describe("axios",async ()=>{
//     const wrapper = shallowMount(information, {
//         mocks: {
//             axios
//         },
//         localVue
//     });
//     it("axios",async ()=>{
//         expect(wrapper.vm.update()).resolves.toBeTruthy();
//
//     })
// })








