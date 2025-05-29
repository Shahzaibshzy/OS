import { Menu } from "@headlessui/react";
import { ChevronDownIcon } from "@heroicons/react/20/solid";

export default function Dropdown() {
  return (
    <div className="flex justify-center w-full mt-10">
    <Menu as="div" className="relative inline-block text-left">
      <div>
        <Menu.Button className="inline-flex w-full justify-center gap-x-1.5 rounded-md bg-white px-3 py-2 text-sm md:text-base font-semibold text-gray-900 shadow-sm ring-1 ring-inset ring-gray-300 hover:bg-gray-50">
          Options
          <ChevronDownIcon
            aria-hidden="true"
            className="-mr-1 h-5 w-5 text-gray-400"
          />
        </Menu.Button>
      </div>

      <Menu.Items
        className="absolute right-0 z-10 mt-2 w-48 sm:w-56 md:w-64 lg:w-72 origin-top-right rounded-md bg-white shadow-lg ring-1 ring-black/5 focus:outline-none"
      >
        <div className="py-1">
          <Menu.Item>
            {({ active }) => (
              <a
                href="#"
                className={`block px-4 py-2 text-sm md:text-base ${
                  active ? "bg-gray-100 text-gray-900" : "text-gray-700"
                }`}
              >
                Account settings
              </a>
            )}
          </Menu.Item>
          <Menu.Item>
            {({ active }) => (
              <a
                href="#"
                className={`block px-4 py-2 text-sm md:text-base ${
                  active ? "bg-gray-100 text-gray-900" : "text-gray-700"
                }`}
              >
                Support
              </a>
            )}
          </Menu.Item>
          <Menu.Item>
            {({ active }) => (
              <a
                href="#"
                className={`block px-4 py-2 text-sm md:text-base ${
                  active ? "bg-gray-100 text-gray-900" : "text-gray-700"
                }`}
              >
                License
              </a>
            )}
          </Menu.Item>
          <form method="POST" action="#">
            <Menu.Item>
              {({ active }) => (
                <button
                  type="submit"
                  className={`block w-full px-4 py-2 text-left text-sm md:text-base ${
                    active ? "bg-gray-100 text-gray-900" : "text-gray-700"
                  }`}
                >
                  Sign out
                </button>
              )}
            </Menu.Item>
          </form>
        </div>
      </Menu.Items>
    </Menu>
    </div>
  );
}
