"use client";
import React from "react";

export function VersionTable() {
    return (
        <div>
            <div className="relative overflow-x-auto shadow-md sm:rounded-lg">
                <table className="w-full text-sm text-left rtl:text-right text-gray-500 dark:text-gray-400">
                    <thead className="text-xs text-gray-700 uppercase bg-gray-50 dark:bg-gray-700 dark:text-gray-400">
                        <tr>
                            <th scope="col" className="px-6 py-3">
                                File name
                            </th>
                            <th scope="col" className="px-6 py-3">
                                Kind
                            </th>
                            <th scope="col" className="px-6 py-3">
                                OS
                            </th>
                            <th scope="col" className="px-6 py-3">
                                Arch
                            </th>
                            <th scope="col" className="px-6 py-3">
                                Size
                            </th>
                        </tr>
                    </thead>
                    <tbody>
                        <tr className="bg-white border-b dark:bg-gray-800 dark:border-gray-700">
                            <th scope="row" className="px-6 py-4 font-medium text-gray-900 whitespace-nowrap dark:text-white">
                                <a href="https://github.com/iArchitSharma/Sukuna/releases/download/1/sukuna-linux-v1.zip" className="font-medium text-blue-600 dark:text-blue-500 hover:underline">sukuna-linux-v1.zip</a>

                            </th>
                            <td className="px-6 py-4">
                                Archive
                            </td>
                            <td className="px-6 py-4">
                                Linux
                            </td>
                            <td className="px-6 py-4">
                                x86
                            </td>
                            <td className="px-6 py-4">
                                862 KB
                            </td>
                        </tr>
                        <tr className="bg-white border-b dark:bg-gray-800 dark:border-gray-700">
                            <th scope="row" className="px-6 py-4 font-medium text-gray-900 whitespace-nowrap dark:text-white">
                                <a href="https://github.com/iArchitSharma/Sukuna/releases/download/1/sukuna-win-v1.zip" className="font-medium text-blue-600 dark:text-blue-500 hover:underline">sukuna-win-v1.zip</a>
                            </th>
                            <td className="px-6 py-4">
                                Archive
                            </td>
                            <td className="px-6 py-4">
                                Windows
                            </td>
                            <td className="px-6 py-4">
                                x86
                            </td>
                            <td className="px-6 py-4">
                                653 KB
                            </td>
                        </tr>
                        <tr className="bg-white border-b dark:bg-gray-800 dark:border-gray-700">
                            <th scope="row" className="px-6 py-4 font-medium text-gray-900 whitespace-nowrap dark:text-white">
                                <a href="https://github.com/iArchitSharma/Sukuna/archive/refs/tags/1.tar.gz" className="font-medium text-blue-600 dark:text-blue-500 hover:underline">Source code(tar.gz)</a>
                            </th>
                            <td className="px-6 py-4">
                                <b>Source</b>
                            </td>
                            <td className="px-6 py-4">

                            </td>
                            <td className="px-6 py-4">

                            </td>
                            <td className="px-6 py-4">
                                1.47 MB
                            </td>
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>
    );
}