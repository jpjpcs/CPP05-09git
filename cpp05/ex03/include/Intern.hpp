/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:59:42 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:03:15 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include "AForm.hpp"

class Intern 
{
    public:
        Intern();
        Intern(const Intern &src);
        Intern &operator=(const Intern &src);
        ~Intern();

        AForm* makeForm(const std::string &formName, const std::string &target) const;

    private:
        static AForm* createShrubbery(const std::string &target);
        static AForm* createRobotomy(const std::string &target);
        static AForm* createPardon(const std::string &target);

        struct FormPair 
        {
            const char* name;
            AForm* (*creator)(const std::string &target);
        };
};

#endif
