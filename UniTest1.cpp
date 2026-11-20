#include "CppUnitTest.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "../task2_3sem/AirTransport.h"
#include "../task2_3sem/CargoOrder.h"
#include "../task2_3sem/Client.h"
#include "../task2_3sem/RailTransport.h"
#include "../task2_3sem/RiverTransport.h"
#include "../task2_3sem/RoadTransport.h"
#include "../task2_3sem/Route.h"
#include "../task2_3sem/SeaTransport.h"
#include "../task2_3sem/Transport.h"
#include "../task2_3sem/TransportCompany.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
    constexpr double kTolerance = 1e-6;

    TEST_CLASS(TransportBaseTests)
    {
    public:
        /**
         * @brief Проверка форматирования вещественных чисел Transport::FormatDouble
         */
        TEST_METHOD(FormatDouble_VariousValues_Success)
        {
            Assert::AreEqual(std::string("0.00"), Transport::FormatDouble(0.0));
            Assert::AreEqual(std::string("12.35"), Transport::FormatDouble(12.346));
            Assert::AreEqual(std::string("5.05"), Transport::FormatDouble(5.05));
            Assert::AreEqual(std::string("-3.07"), Transport::FormatDouble(-3.07));
            Assert::AreEqual(std::string("1000.00"), Transport::FormatDouble(1000.0));
        }

        /**
         * @brief Проверка полиморфного вызова GetTransportType и CalculateDeliveryCost через базовый указатель
         */
        TEST_METHOD(PolymorphicCollection_AllFiveTypes_Success)
        {
            // Arrange
            std::vector<std::unique_ptr<Transport>> fleet;
            fleet.push_back(std::make_unique<AirTransport>("AIR-1", "Ан-124", 120.0, 800.0, 15.0, 11000.0, 5000.0));
            fleet.push_back(std::make_unique<RiverTransport>("RIV-1", "Волго-Дон", 5000.0, 20.0, 2.0, 3.5, 1200.0));
            fleet.push_back(std::make_unique<SeaTransport>("SEA-1", "Балтика", 20000.0, 35.0, 1.5, 1500, 8000.0));
            fleet.push_back(std::make_unique<RailTransport>("RAIL-1", "ВЛ80", 3000.0, 70.0, 3.0, 50, 2500.0));
            fleet.push_back(std::make_unique<RoadTransport>("ROAD-1", "КАМАЗ-5490", 20.0, 85.0, 5.0, 4, 1500.0));

            // Act & Assert
            Assert::AreEqual(std::string("Воздушный"), fleet[0]->GetTransportType());
            Assert::AreEqual(155000.0, fleet[0]->CalculateDeliveryCost(1000.0, 10.0), kTolerance);

            Assert::AreEqual(std::string("Речной"), fleet[1]->GetTransportType());
            Assert::AreEqual(101200.0, fleet[1]->CalculateDeliveryCost(500.0, 100.0), kTolerance);

            Assert::AreEqual(std::string("Морской"), fleet[2]->GetTransportType());
            Assert::AreEqual(608000.0, fleet[2]->CalculateDeliveryCost(2000.0, 200.0), kTolerance);

            Assert::AreEqual(std::string("Железнодорожный"), fleet[3]->GetTransportType());
            Assert::AreEqual(122500.0, fleet[3]->CalculateDeliveryCost(800.0, 50.0), kTolerance);

            Assert::AreEqual(std::string("Автомобильный"), fleet[4]->GetTransportType());
            Assert::AreEqual(36500.0, fleet[4]->CalculateDeliveryCost(700.0, 10.0), kTolerance);
        }

        /**
         * @brief Проверка базовых сеттеров и геттеров Transport
         */
        TEST_METHOD(BaseGettersAndSetters_ValidValues_Success)
        {
            // Arrange
            RoadTransport truck;

            // Act
            truck.SetId("TR-99");
            truck.SetName("Volvo FH");
            truck.SetCapacityTons(25.5);
            truck.SetSpeedKmH(90.0);
            truck.SetRatePerTonKm(6.5);

            // Assert
            Assert::AreEqual(std::string("TR-99"), truck.GetId());
            Assert::AreEqual(std::string("Volvo FH"), truck.GetName());
            Assert::AreEqual(25.5, truck.GetCapacityTons(), kTolerance);
            Assert::AreEqual(90.0, truck.GetSpeedKmH(), kTolerance);
            Assert::AreEqual(6.5, truck.GetRatePerTonKm(), kTolerance);
        }

        /**
         * @brief Проверка валидации базовых сеттеров Transport
         */
        TEST_METHOD(BaseSetters_InvalidValues_Throws)
        {
            RoadTransport truck;

            Assert::ExpectException<std::invalid_argument>([&]() { truck.SetId(""); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.SetId("   "); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.SetName(""); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.SetName("\t\n"); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.SetCapacityTons(0.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.SetCapacityTons(-10.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.SetSpeedKmH(0.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.SetSpeedKmH(-5.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.SetRatePerTonKm(-0.01); });
        }

        /**
         * @brief Проверка исключений при расчете стоимости доставки с некорректными аргументами
         */
        TEST_METHOD(CalculateDeliveryCost_InvalidArguments_Throws)
        {
            RoadTransport truck("ROAD-1", "КАМАЗ", 20.0, 85.0, 5.0, 4, 1500.0);

            Assert::ExpectException<std::invalid_argument>([&]() { truck.CalculateDeliveryCost(0.0, 10.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.CalculateDeliveryCost(-100.0, 10.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.CalculateDeliveryCost(100.0, 0.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.CalculateDeliveryCost(100.0, -5.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { truck.CalculateDeliveryCost(100.0, 20.01); });
        }

        /**
         * @brief Проверка граничного случая: вес груза точно равен грузоподъемности и нулевой тариф
         */
        TEST_METHOD(CalculateDeliveryCost_ExactCapacityAndZeroRate_Success)
        {
            // Arrange
            RoadTransport truck("ROAD-1", "КАМАЗ", 20.0, 80.0, 0.0, 4, 500.0);

            // Act
            const double cost = truck.CalculateDeliveryCost(300.0, 20.0);

            // Assert
            Assert::AreEqual(500.0, cost, kTolerance);
        }

        /**
         * @brief Проверка сравнения объектов разных типов-наследников через базовый класс Transport
         */
        TEST_METHOD(BaseEquality_DifferentDerivedTypes_NotEqual)
        {
            // Arrange
            AirTransport air("ID-1", "Единица", 100.0, 100.0, 5.0, 10000.0, 0.0);
            SeaTransport sea("ID-1", "Единица", 100.0, 100.0, 5.0, 500, 0.0);

            const Transport& baseAir = air;
            const Transport& baseSea = sea;

            // Act & Assert
            Assert::IsFalse(baseAir == baseSea);
            Assert::IsTrue(baseAir != baseSea);
            Assert::IsTrue(air.GetSummary().find("Воздушный") != std::string::npos);
            Assert::IsTrue(sea.GetSummary().find("Морской") != std::string::npos);
        }
    };

    TEST_CLASS(AirTransportTests)
    {
    public:
        TEST_METHOD(Constructor_Default_Success)
        {
            AirTransport air;

            Assert::AreEqual(std::string("TR-0"), air.GetId());
            Assert::AreEqual(10000.0, air.GetMaxAltitudeMeters(), kTolerance);
            Assert::AreEqual(0.0, air.GetAirportFee(), kTolerance);
            Assert::AreEqual(std::string("Воздушный"), air.GetTransportType());
        }

        TEST_METHOD(Constructor_Parameters_Success)
        {
            AirTransport air("AIR-1", "Ил-76", 50.0, 780.0, 14.0, 10500.0, 4500.0);

            Assert::AreEqual(std::string("AIR-1"), air.GetId());
            Assert::AreEqual(std::string("Ил-76"), air.GetName());
            Assert::AreEqual(50.0, air.GetCapacityTons(), kTolerance);
            Assert::AreEqual(780.0, air.GetSpeedKmH(), kTolerance);
            Assert::AreEqual(14.0, air.GetRatePerTonKm(), kTolerance);
            Assert::AreEqual(10500.0, air.GetMaxAltitudeMeters(), kTolerance);
            Assert::AreEqual(4500.0, air.GetAirportFee(), kTolerance);
        }

        TEST_METHOD(RuleOfFive_AndSelfAssignment_Success)
        {
            // Arrange
            AirTransport original("AIR-1", "Ан-124", 120.0, 800.0, 15.0, 11000.0, 5000.0);

            // Act
            AirTransport copy(original);
            AirTransport assigned;
            assigned = original;
            assigned = assigned; // самоприсваивание

            AirTransport moved(std::move(copy));
            AirTransport moveAssigned;
            moveAssigned = std::move(assigned);

            // Assert
            Assert::IsTrue(original == moved);
            Assert::IsTrue(original == moveAssigned);
            Assert::AreEqual(11000.0, moveAssigned.GetMaxAltitudeMeters(), kTolerance);
            Assert::AreEqual(5000.0, moveAssigned.GetAirportFee(), kTolerance);
        }

        TEST_METHOD(GettersSetters_ValidAndInvalid_Success)
        {
            AirTransport air;
            air.SetMaxAltitudeMeters(12500.0);
            air.SetAirportFee(6200.0);

            Assert::AreEqual(12500.0, air.GetMaxAltitudeMeters(), kTolerance);
            Assert::AreEqual(6200.0, air.GetAirportFee(), kTolerance);

            Assert::ExpectException<std::invalid_argument>([&]() { air.SetMaxAltitudeMeters(0.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { air.SetMaxAltitudeMeters(-100.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { air.SetAirportFee(-1.0); });
        }

        TEST_METHOD(Constructor_InvalidParams_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([]() {
                AirTransport bad("AIR-1", "Ил-76", 50.0, 780.0, 14.0, 0.0, 1000.0);
                });
            Assert::ExpectException<std::invalid_argument>([]() {
                AirTransport bad("AIR-1", "Ил-76", 50.0, 780.0, 14.0, 10000.0, -50.0);
                });
        }

        TEST_METHOD(OperatorsAndToString_Success)
        {
            AirTransport a1("AIR-1", "Ил-76", 50.0, 780.0, 14.0, 10500.0, 4500.0);
            AirTransport a2("AIR-1", "Ил-76", 50.0, 780.0, 14.0, 10500.0, 4500.0);
            AirTransport a3("AIR-1", "Ил-76", 50.0, 780.0, 14.0, 10500.0, 4600.0);

            Assert::IsTrue(a1 == a2);
            Assert::IsFalse(a1 != a2);
            Assert::IsTrue(a1 != a3);

            const std::string text = a1.ToString();
            Assert::IsTrue(text.find("Воздушный") != std::string::npos);
            Assert::IsTrue(text.find("10500.00") != std::string::npos);
            Assert::IsTrue(text.find("4500.00") != std::string::npos);
        }
    };

    TEST_CLASS(RiverTransportTests)
    {
    public:
        TEST_METHOD(Constructor_Default_Success)
        {
            RiverTransport river;

            Assert::AreEqual(2.0, river.GetDraftMeters(), kTolerance);
            Assert::AreEqual(0.0, river.GetLockPassageFee(), kTolerance);
            Assert::AreEqual(std::string("Речной"), river.GetTransportType());
        }

        TEST_METHOD(Constructor_Parameters_Success)
        {
            RiverTransport river("RIV-1", "Волго-Дон", 5000.0, 20.0, 2.0, 3.6, 1500.0);

            Assert::AreEqual(std::string("RIV-1"), river.GetId());
            Assert::AreEqual(3.6, river.GetDraftMeters(), kTolerance);
            Assert::AreEqual(1500.0, river.GetLockPassageFee(), kTolerance);
            Assert::AreEqual(21500.0, river.CalculateDeliveryCost(100.0, 100.0), kTolerance);
        }

        TEST_METHOD(RuleOfFive_AndSelfAssignment_Success)
        {
            RiverTransport original("RIV-1", "Баржа-1", 3000.0, 15.0, 1.8, 2.8, 900.0);

            RiverTransport copy(original);
            RiverTransport assigned;
            assigned = original;
            assigned = assigned;

            RiverTransport moved(std::move(copy));
            RiverTransport moveAssigned;
            moveAssigned = std::move(assigned);

            Assert::IsTrue(original == moved);
            Assert::IsTrue(original == moveAssigned);
        }

        TEST_METHOD(GettersSetters_ValidAndInvalid_Success)
        {
            RiverTransport river;
            river.SetDraftMeters(4.2);
            river.SetLockPassageFee(2100.0);

            Assert::AreEqual(4.2, river.GetDraftMeters(), kTolerance);
            Assert::AreEqual(2100.0, river.GetLockPassageFee(), kTolerance);

            Assert::ExpectException<std::invalid_argument>([&]() { river.SetDraftMeters(0.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { river.SetDraftMeters(-1.5); });
            Assert::ExpectException<std::invalid_argument>([&]() { river.SetLockPassageFee(-10.0); });
        }

        TEST_METHOD(Constructor_InvalidParams_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([]() {
                RiverTransport bad("RIV-1", "Баржа", 1000.0, 15.0, 2.0, -2.0, 500.0);
                });
            Assert::ExpectException<std::invalid_argument>([]() {
                RiverTransport bad("RIV-1", "Баржа", 1000.0, 15.0, 2.0, 2.0, -500.0);
                });
        }

        TEST_METHOD(OperatorsAndToString_Success)
        {
            RiverTransport r1("RIV-1", "Волго-Дон", 5000.0, 20.0, 2.0, 3.5, 1200.0);
            RiverTransport r2("RIV-1", "Волго-Дон", 5000.0, 20.0, 2.0, 3.5, 1200.0);
            RiverTransport r3("RIV-1", "Волго-Дон", 5000.0, 20.0, 2.0, 4.0, 1200.0);

            Assert::IsTrue(r1 == r2);
            Assert::IsTrue(r1 != r3);

            const std::string text = r1.ToString();
            Assert::IsTrue(text.find("Речной") != std::string::npos);
            Assert::IsTrue(text.find("3.50") != std::string::npos);
            Assert::IsTrue(text.find("1200.00") != std::string::npos);
        }
    };

    TEST_CLASS(SeaTransportTests)
    {
    public:
        TEST_METHOD(Constructor_Default_Success)
        {
            SeaTransport sea;

            Assert::AreEqual(100, sea.GetContainerCapacityTeu());
            Assert::AreEqual(0.0, sea.GetPortFee(), kTolerance);
            Assert::AreEqual(std::string("Морской"), sea.GetTransportType());
        }

        TEST_METHOD(Constructor_Parameters_Success)
        {
            SeaTransport sea("SEA-1", "Балтика", 20000.0, 35.0, 1.5, 1500, 8000.0);

            Assert::AreEqual(1500, sea.GetContainerCapacityTeu());
            Assert::AreEqual(8000.0, sea.GetPortFee(), kTolerance);
            Assert::AreEqual(158000.0, sea.CalculateDeliveryCost(1000.0, 100.0), kTolerance);
        }

        TEST_METHOD(RuleOfFive_AndSelfAssignment_Success)
        {
            SeaTransport original("SEA-1", "Нева", 15000.0, 30.0, 1.4, 1200, 7500.0);

            SeaTransport copy(original);
            SeaTransport assigned;
            assigned = original;
            assigned = assigned;

            SeaTransport moved(std::move(copy));
            SeaTransport moveAssigned;
            moveAssigned = std::move(assigned);

            Assert::IsTrue(original == moved);
            Assert::IsTrue(original == moveAssigned);
        }

        TEST_METHOD(GettersSetters_ValidAndInvalid_Success)
        {
            SeaTransport sea;
            sea.SetContainerCapacityTeu(2400);
            sea.SetPortFee(9500.0);

            Assert::AreEqual(2400, sea.GetContainerCapacityTeu());
            Assert::AreEqual(9500.0, sea.GetPortFee(), kTolerance);

            Assert::ExpectException<std::invalid_argument>([&]() { sea.SetContainerCapacityTeu(0); });
            Assert::ExpectException<std::invalid_argument>([&]() { sea.SetContainerCapacityTeu(-50); });
            Assert::ExpectException<std::invalid_argument>([&]() { sea.SetPortFee(-1.0); });
        }

        TEST_METHOD(Constructor_InvalidParams_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([]() {
                SeaTransport bad("SEA-1", "Судно", 10000.0, 30.0, 1.5, 0, 5000.0);
                });
            Assert::ExpectException<std::invalid_argument>([]() {
                SeaTransport bad("SEA-1", "Судно", 10000.0, 30.0, 1.5, 500, -100.0);
                });
        }

        TEST_METHOD(OperatorsAndToString_Success)
        {
            SeaTransport s1("SEA-1", "Балтика", 20000.0, 35.0, 1.5, 1500, 8000.0);
            SeaTransport s2("SEA-1", "Балтика", 20000.0, 35.0, 1.5, 1500, 8000.0);
            SeaTransport s3("SEA-1", "Балтика", 20000.0, 35.0, 1.5, 1600, 8000.0);

            Assert::IsTrue(s1 == s2);
            Assert::IsTrue(s1 != s3);

            const std::string text = s1.ToString();
            Assert::IsTrue(text.find("Морской") != std::string::npos);
            Assert::IsTrue(text.find("1500 TEU") != std::string::npos);
            Assert::IsTrue(text.find("8000.00") != std::string::npos);
        }
    };

    TEST_CLASS(RailTransportTests)
    {
    public:
        TEST_METHOD(Constructor_Default_Success)
        {
            RailTransport rail;

            Assert::AreEqual(1, rail.GetWagonCount());
            Assert::AreEqual(0.0, rail.GetStationHandlingFee(), kTolerance);
            Assert::AreEqual(std::string("Железнодорожный"), rail.GetTransportType());
        }

        TEST_METHOD(Constructor_Parameters_Success)
        {
            RailTransport rail("RAIL-1", "ВЛ80", 3000.0, 70.0, 3.0, 50, 2500.0);

            Assert::AreEqual(50, rail.GetWagonCount());
            Assert::AreEqual(2500.0, rail.GetStationHandlingFee(), kTolerance);
            Assert::AreEqual(62500.0, rail.CalculateDeliveryCost(500.0, 40.0), kTolerance);
        }

        TEST_METHOD(RuleOfFive_AndSelfAssignment_Success)
        {
            RailTransport original("RAIL-1", "2ЭС6 Синара", 4000.0, 80.0, 2.8, 60, 3000.0);

            RailTransport copy(original);
            RailTransport assigned;
            assigned = original;
            assigned = assigned;

            RailTransport moved(std::move(copy));
            RailTransport moveAssigned;
            moveAssigned = std::move(assigned);

            Assert::IsTrue(original == moved);
            Assert::IsTrue(original == moveAssigned);
        }

        TEST_METHOD(GettersSetters_ValidAndInvalid_Success)
        {
            RailTransport rail;
            rail.SetWagonCount(65);
            rail.SetStationHandlingFee(3200.0);

            Assert::AreEqual(65, rail.GetWagonCount());
            Assert::AreEqual(3200.0, rail.GetStationHandlingFee(), kTolerance);

            Assert::ExpectException<std::invalid_argument>([&]() { rail.SetWagonCount(0); });
            Assert::ExpectException<std::invalid_argument>([&]() { rail.SetWagonCount(-5); });
            Assert::ExpectException<std::invalid_argument>([&]() { rail.SetStationHandlingFee(-1.0); });
        }

        TEST_METHOD(Constructor_InvalidParams_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([]() {
                RailTransport bad("RAIL-1", "ВЛ80", 3000.0, 70.0, 3.0, 0, 1000.0);
                });
            Assert::ExpectException<std::invalid_argument>([]() {
                RailTransport bad("RAIL-1", "ВЛ80", 3000.0, 70.0, 3.0, 10, -100.0);
                });
        }

        TEST_METHOD(OperatorsAndToString_Success)
        {
            RailTransport r1("RAIL-1", "ВЛ80", 3000.0, 70.0, 3.0, 50, 2500.0);
            RailTransport r2("RAIL-1", "ВЛ80", 3000.0, 70.0, 3.0, 50, 2500.0);
            RailTransport r3("RAIL-1", "ВЛ80", 3000.0, 70.0, 3.0, 40, 2500.0);

            Assert::IsTrue(r1 == r2);
            Assert::IsTrue(r1 != r3);

            const std::string text = r1.ToString();
            Assert::IsTrue(text.find("Железнодорожный") != std::string::npos);
            Assert::IsTrue(text.find("Вагонов: 50") != std::string::npos);
            Assert::IsTrue(text.find("2500.00") != std::string::npos);
        }
    };

    TEST_CLASS(RoadTransportTests)
    {
    public:
        TEST_METHOD(Constructor_Default_Success)
        {
            RoadTransport road;

            Assert::AreEqual(2, road.GetAxleCount());
            Assert::AreEqual(0.0, road.GetTollRoadFee(), kTolerance);
            Assert::AreEqual(std::string("Автомобильный"), road.GetTransportType());
        }

        TEST_METHOD(Constructor_Parameters_Success)
        {
            RoadTransport road("ROAD-1", "КАМАЗ-5490", 20.0, 85.0, 5.0, 4, 1500.0);

            Assert::AreEqual(4, road.GetAxleCount());
            Assert::AreEqual(1500.0, road.GetTollRoadFee(), kTolerance);
            Assert::AreEqual(36500.0, road.CalculateDeliveryCost(700.0, 10.0), kTolerance);
        }

        TEST_METHOD(RuleOfFive_AndSelfAssignment_Success)
        {
            RoadTransport original("ROAD-1", "Scania R500", 22.0, 90.0, 5.5, 5, 1800.0);

            RoadTransport copy(original);
            RoadTransport assigned;
            assigned = original;
            assigned = assigned;

            RoadTransport moved(std::move(copy));
            RoadTransport moveAssigned;
            moveAssigned = std::move(assigned);

            Assert::IsTrue(original == moved);
            Assert::IsTrue(original == moveAssigned);
        }

        TEST_METHOD(GettersSetters_ValidAndInvalid_Success)
        {
            RoadTransport road;
            road.SetAxleCount(6);
            road.SetTollRoadFee(2200.0);

            Assert::AreEqual(6, road.GetAxleCount());
            Assert::AreEqual(2200.0, road.GetTollRoadFee(), kTolerance);

            Assert::ExpectException<std::invalid_argument>([&]() { road.SetAxleCount(1); });
            Assert::ExpectException<std::invalid_argument>([&]() { road.SetAxleCount(0); });
            Assert::ExpectException<std::invalid_argument>([&]() { road.SetTollRoadFee(-1.0); });
        }

        TEST_METHOD(Constructor_InvalidParams_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([]() {
                RoadTransport bad("ROAD-1", "Грузовик", 10.0, 80.0, 5.0, 1, 500.0);
                });
            Assert::ExpectException<std::invalid_argument>([]() {
                RoadTransport bad("ROAD-1", "Грузовик", 10.0, 80.0, 5.0, 3, -50.0);
                });
        }

        TEST_METHOD(OperatorsAndToString_Success)
        {
            RoadTransport r1("ROAD-1", "КАМАЗ", 20.0, 85.0, 5.0, 4, 1500.0);
            RoadTransport r2("ROAD-1", "КАМАЗ", 20.0, 85.0, 5.0, 4, 1500.0);
            RoadTransport r3("ROAD-1", "КАМАЗ", 20.0, 85.0, 5.0, 5, 1500.0);

            Assert::IsTrue(r1 == r2);
            Assert::IsTrue(r1 != r3);

            const std::string text = r1.ToString();
            Assert::IsTrue(text.find("Автомобильный") != std::string::npos);
            Assert::IsTrue(text.find("Осей: 4") != std::string::npos);
            Assert::IsTrue(text.find("1500.00") != std::string::npos);
        }
    };

    TEST_CLASS(RouteTests)
    {
    public:
        TEST_METHOD(Constructor_DefaultAndParameters_Success)
        {
            Route defRoute;
            Assert::AreEqual(std::string("R-0"), defRoute.GetId());
            Assert::AreEqual(1.0, defRoute.GetDistanceKm(), kTolerance);
            Assert::AreEqual(0.0, defRoute.GetBasePrice(), kTolerance);

            Route route("R-1", "Москва", "Санкт-Петербург", 700.0, 3500.0);
            Assert::AreEqual(std::string("R-1"), route.GetId());
            Assert::AreEqual(std::string("Москва"), route.GetOrigin());
            Assert::AreEqual(std::string("Санкт-Петербург"), route.GetDestination());
            Assert::AreEqual(700.0, route.GetDistanceKm(), kTolerance);
            Assert::AreEqual(3500.0, route.GetBasePrice(), kTolerance);
            Assert::AreEqual(std::string("Москва -> Санкт-Петербург"), route.GetRouteName());
        }

        TEST_METHOD(RuleOfFive_AndSelfAssignment_Success)
        {
            Route original("R-10", "Казань", "Самара", 360.0, 2400.0);

            Route copy(original);
            Route assigned;
            assigned = original;
            assigned = assigned;

            Route moved(std::move(copy));
            Route moveAssigned;
            moveAssigned = std::move(assigned);

            Assert::IsTrue(original == moved);
            Assert::IsTrue(original == moveAssigned);
        }

        TEST_METHOD(GettersSetters_ValidValues_Success)
        {
            Route route;
            route.SetId("R-5");
            route.SetOrigin("Пермь");
            route.SetDestination("Екатеринбург");
            route.SetDistanceKm(365.0);
            route.SetBasePrice(2900.0);

            Assert::AreEqual(std::string("R-5"), route.GetId());
            Assert::AreEqual(std::string("Пермь"), route.GetOrigin());
            Assert::AreEqual(std::string("Екатеринбург"), route.GetDestination());
            Assert::AreEqual(365.0, route.GetDistanceKm(), kTolerance);
            Assert::AreEqual(2900.0, route.GetBasePrice(), kTolerance);
        }

        TEST_METHOD(Constructor_InvalidParams_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([]() { Route r("", "А", "Б", 100.0, 500.0); });
            Assert::ExpectException<std::invalid_argument>([]() { Route r("R-1", "  ", "Б", 100.0, 500.0); });
            Assert::ExpectException<std::invalid_argument>([]() { Route r("R-1", "А", "", 100.0, 500.0); });
            Assert::ExpectException<std::invalid_argument>([]() { Route r("R-1", "А", "Б", 0.0, 500.0); });
            Assert::ExpectException<std::invalid_argument>([]() { Route r("R-1", "А", "Б", -10.0, 500.0); });
            Assert::ExpectException<std::invalid_argument>([]() { Route r("R-1", "А", "Б", 100.0, -1.0); });
        }

        TEST_METHOD(Setters_InvalidParams_Throws)
        {
            Route route("R-1", "А", "Б", 100.0, 500.0);

            Assert::ExpectException<std::invalid_argument>([&]() { route.SetId(""); });
            Assert::ExpectException<std::invalid_argument>([&]() { route.SetOrigin("   "); });
            Assert::ExpectException<std::invalid_argument>([&]() { route.SetDestination(""); });
            Assert::ExpectException<std::invalid_argument>([&]() { route.SetDistanceKm(0.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { route.SetBasePrice(-10.0); });
        }

        TEST_METHOD(OperatorsAndToString_Success)
        {
            Route r1("R-1", "Москва", "Тверь", 180.0, 1500.0);
            Route r2("R-1", "Москва", "Тверь", 180.0, 1500.0);
            Route r3("R-2", "Москва", "Тверь", 180.0, 1500.0);

            Assert::IsTrue(r1 == r2);
            Assert::IsFalse(r1 != r2);
            Assert::IsTrue(r1 != r3);

            const std::string text = r1.ToString();
            Assert::IsTrue(text.find("[R-1]") != std::string::npos);
            Assert::IsTrue(text.find("Москва -> Тверь") != std::string::npos);
            Assert::IsTrue(text.find("180.00") != std::string::npos);
            Assert::IsTrue(text.find("1500.00") != std::string::npos);
        }
    };

    TEST_CLASS(ClientTests)
    {
    public:
        TEST_METHOD(Constructor_DefaultAndParameters_Success)
        {
            Client defClient;
            Assert::AreEqual(std::string("CL-0"), defClient.GetId());
            Assert::IsFalse(defClient.IsRegular());
            Assert::AreEqual(0.0, defClient.GetDiscountPercent(), kTolerance);

            Client client("CL-1", "АО Металлург", true, 12.5);
            Assert::AreEqual(std::string("CL-1"), client.GetId());
            Assert::AreEqual(std::string("АО Металлург"), client.GetName());
            Assert::IsTrue(client.IsRegular());
            Assert::AreEqual(12.5, client.GetDiscountPercent(), kTolerance);
            Assert::AreEqual(12.5, client.GetEffectiveDiscountPercent(), kTolerance);
        }

        TEST_METHOD(RuleOfFive_AndSelfAssignment_Success)
        {
            Client original("CL-7", "ООО Вектор", true, 10.0);

            Client copy(original);
            Client assigned;
            assigned = original;
            assigned = assigned;

            Client moved(std::move(copy));
            Client moveAssigned;
            moveAssigned = std::move(assigned);

            Assert::IsTrue(original == moved);
            Assert::IsTrue(original == moveAssigned);
        }

        TEST_METHOD(EffectiveDiscount_BoundaryAndRegularFlag_Success)
        {
            Client ordinary("C-1", "Обычный", false, 20.0);
            Assert::AreEqual(20.0, ordinary.GetDiscountPercent(), kTolerance);
            Assert::AreEqual(0.0, ordinary.GetEffectiveDiscountPercent(), kTolerance);

            ordinary.SetRegular(true);
            Assert::AreEqual(20.0, ordinary.GetEffectiveDiscountPercent(), kTolerance);

            ordinary.SetDiscountPercent(0.0);
            Assert::AreEqual(0.0, ordinary.GetEffectiveDiscountPercent(), kTolerance);

            ordinary.SetDiscountPercent(100.0);
            Assert::AreEqual(100.0, ordinary.GetEffectiveDiscountPercent(), kTolerance);
        }

        TEST_METHOD(Constructor_InvalidParams_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([]() { Client c("", "Имя", false, 0.0); });
            Assert::ExpectException<std::invalid_argument>([]() { Client c("C-1", "   ", false, 0.0); });
            Assert::ExpectException<std::invalid_argument>([]() { Client c("C-1", "Имя", true, -0.1); });
            Assert::ExpectException<std::invalid_argument>([]() { Client c("C-1", "Имя", true, 100.1); });
        }

        TEST_METHOD(Setters_ValidAndInvalid_Success)
        {
            Client client("C-1", "Имя", false, 5.0);
            client.SetId("C-2");
            client.SetName("Новое Имя");
            Assert::AreEqual(std::string("C-2"), client.GetId());
            Assert::AreEqual(std::string("Новое Имя"), client.GetName());

            Assert::ExpectException<std::invalid_argument>([&]() { client.SetId(""); });
            Assert::ExpectException<std::invalid_argument>([&]() { client.SetName("  "); });
            Assert::ExpectException<std::invalid_argument>([&]() { client.SetDiscountPercent(-5.0); });
            Assert::ExpectException<std::invalid_argument>([&]() { client.SetDiscountPercent(105.0); });
        }

        TEST_METHOD(OperatorsAndToString_Success)
        {
            Client c1("C-1", "Иванов", true, 15.0);
            Client c2("C-1", "Иванов", true, 15.0);
            Client c3("C-1", "Иванов", false, 15.0);

            Assert::IsTrue(c1 == c2);
            Assert::IsFalse(c1 != c2);
            Assert::IsTrue(c1 != c3);

            Assert::IsTrue(c1.ToString().find("Постоянный") != std::string::npos);
            Assert::IsTrue(c1.ToString().find("15.00%") != std::string::npos);
            Assert::IsTrue(c3.ToString().find("Обычный") != std::string::npos);
            Assert::IsTrue(c3.ToString().find("0.00%") != std::string::npos);
        }
    };

    TEST_CLASS(CargoOrderTests)
    {
    public:
        TEST_METHOD(Constructor_Default_Behavior)
        {
            CargoOrder emptyOrder;

            Assert::AreEqual(0, emptyOrder.GetId());
            Assert::IsNull(emptyOrder.GetClient());
            Assert::IsNull(emptyOrder.GetRoute());
            Assert::IsNull(emptyOrder.GetTransport());
            Assert::AreEqual(0.0, emptyOrder.GetWeightTons(), kTolerance);
            Assert::AreEqual(0.0, emptyOrder.GetFreightTurnover(), kTolerance);
            Assert::IsTrue(emptyOrder.ToString().find("не заполнен") != std::string::npos);

            Assert::ExpectException<std::logic_error>([&]() {
                emptyOrder.CalculateCost();
                });
        }

        TEST_METHOD(Constructor_Parameters_AndGetters_Success)
        {
            Client client("C-1", "ООО Груз", false, 0.0);
            Route route("R-1", "Москва", "Тверь", 200.0, 1000.0);
            RoadTransport truck("ROAD-1", "КАМАЗ", 20.0, 80.0, 5.0, 4, 500.0);

            CargoOrder order(10, &client, &route, &truck, "Стройматериалы", 12.0);

            Assert::AreEqual(10, order.GetId());
            Assert::IsTrue(&client == order.GetClient());
            Assert::IsTrue(&route == order.GetRoute());
            Assert::IsTrue(&truck == order.GetTransport());
            Assert::AreEqual(std::string("Стройматериалы"), order.GetCargoName());
            Assert::AreEqual(12.0, order.GetWeightTons(), kTolerance);
        }

        TEST_METHOD(Constructor_InvalidParams_Throws)
        {
            Client client("C-1", "ООО Груз", false, 0.0);
            Route route("R-1", "Москва", "Тверь", 200.0, 1000.0);
            RoadTransport truck("ROAD-1", "КАМАЗ", 20.0, 80.0, 5.0, 4, 500.0);

            Assert::ExpectException<std::invalid_argument>([&]() {
                CargoOrder o(0, &client, &route, &truck, "Груз", 5.0);
                });
            Assert::ExpectException<std::invalid_argument>([&]() {
                CargoOrder o(1, nullptr, &route, &truck, "Груз", 5.0);
                });
            Assert::ExpectException<std::invalid_argument>([&]() {
                CargoOrder o(1, &client, nullptr, &truck, "Груз", 5.0);
                });
            Assert::ExpectException<std::invalid_argument>([&]() {
                CargoOrder o(1, &client, &route, nullptr, "Груз", 5.0);
                });
            Assert::ExpectException<std::invalid_argument>([&]() {
                CargoOrder o(1, &client, &route, &truck, "   ", 5.0);
                });
            Assert::ExpectException<std::invalid_argument>([&]() {
                CargoOrder o(1, &client, &route, &truck, "Груз", 0.0);
                });
            Assert::ExpectException<std::invalid_argument>([&]() {
                CargoOrder o(1, &client, &route, &truck, "Груз", 25.0); // > capacity
                });
        }

        TEST_METHOD(RuleOfFive_AndSelfAssignment_Success)
        {
            Client client("C-1", "ООО Груз", true, 10.0);
            Route route("R-1", "Москва", "Тверь", 200.0, 1000.0);
            RoadTransport truck("ROAD-1", "КАМАЗ", 20.0, 80.0, 5.0, 4, 500.0);
            CargoOrder original(5, &client, &route, &truck, "Мебель", 8.0);

            CargoOrder copy(original);
            CargoOrder assigned;
            assigned = original;
            assigned = assigned;

            CargoOrder moved(std::move(copy));
            CargoOrder moveAssigned;
            moveAssigned = std::move(assigned);

            Assert::IsTrue(original == moved);
            Assert::IsTrue(original == moveAssigned);
        }

        TEST_METHOD(CalculateCost_RegularVsOrdinaryAndFullDiscount_Success)
        {
            Route route("R-1", "Москва", "Санкт-Петербург", 700.0, 3500.0);
            RoadTransport truck("ROAD-1", "КАМАЗ", 20.0, 85.0, 5.0, 4, 1500.0);
            Client ordinary("C-1", "Обычный", false, 15.0);
            Client regular("C-2", "Постоянный", true, 15.0);
            Client vip("C-3", "Партнер", true, 100.0);

            // rawCost = 3500 + (700 * 10 * 5 + 1500) = 40000
            CargoOrder o1(1, &ordinary, &route, &truck, "Техника", 10.0);
            CargoOrder o2(2, &regular, &route, &truck, "Техника", 10.0);
            CargoOrder o3(3, &vip, &route, &truck, "Техника", 10.0);

            Assert::AreEqual(40000.0, o1.CalculateCost(), kTolerance);
            Assert::AreEqual(34000.0, o2.CalculateCost(), kTolerance);
            Assert::AreEqual(0.0, o3.CalculateCost(), kTolerance);
        }

        TEST_METHOD(GetFreightTurnover_Success)
        {
            Client client("C-1", "ООО Груз", false, 0.0);
            Route route("R-1", "Москва", "Казань", 820.0, 4000.0);
            RailTransport train("RAIL-1", "ВЛ80", 3000.0, 70.0, 3.0, 50, 2500.0);
            CargoOrder order(1, &client, &route, &train, "Уголь", 125.5);

            Assert::AreEqual(102910.0, order.GetFreightTurnover(), kTolerance);
        }

        TEST_METHOD(OperatorsAndToString_Success)
        {
            Client client("C-1", "ООО Груз", false, 0.0);
            Route route("R-1", "Москва", "Тверь", 200.0, 1000.0);
            RoadTransport truck("ROAD-1", "КАМАЗ", 20.0, 80.0, 5.0, 4, 500.0);

            CargoOrder o1(1, &client, &route, &truck, "Хлеб", 5.0);
            CargoOrder o2(1, &client, &route, &truck, "Хлеб", 5.0);
            CargoOrder o3(2, &client, &route, &truck, "Хлеб", 5.0);

            Assert::IsTrue(o1 == o2);
            Assert::IsFalse(o1 != o2);
            Assert::IsTrue(o1 != o3);

            const std::string text = o1.ToString();
            Assert::IsTrue(text.find("Заказ #1") != std::string::npos);
            Assert::IsTrue(text.find("Хлеб") != std::string::npos);
            Assert::IsTrue(text.find("Москва -> Тверь") != std::string::npos);
        }
    };

    TEST_CLASS(TransportCompanyTests)
    {
    public:
        /**
         * @brief Проверка конструкторов, валидации имени и правила пяти TransportCompany
         */
        TEST_METHOD(ConstructorsAndRuleOfFive_Success)
        {
            TransportCompany defCompany;
            Assert::AreEqual(std::string("Транспортная компания"), defCompany.GetName());

            Assert::ExpectException<std::invalid_argument>([]() { TransportCompany bad(""); });
            Assert::ExpectException<std::invalid_argument>([]() { TransportCompany bad("   "); });
            Assert::ExpectException<std::invalid_argument>([&]() { defCompany.SetName(""); });

            TransportCompany original("Северная Логистика");
            Route r1("R-1", "А", "Б", 100.0, 1000.0);
            original.AddRoute(&r1);

            TransportCompany copy(original);
            TransportCompany assigned;
            assigned = original;
            assigned = assigned;

            TransportCompany moved(std::move(copy));
            TransportCompany moveAssigned;
            moveAssigned = std::move(assigned);

            Assert::AreEqual(std::string("Северная Логистика"), moved.GetName());
            Assert::AreEqual(static_cast<size_t>(1), moved.GetRoutes().size());
            Assert::AreEqual(std::string("Северная Логистика"), moveAssigned.GetName());
            Assert::AreEqual(static_cast<size_t>(1), moveAssigned.GetRoutes().size());
        }

        /**
         * @brief Проверка добавления, поиска и защиты от дубликатов маршрутов, транспорта и клиентов
         */
        TEST_METHOD(RegistryOperations_FindAndDuplicates_Success)
        {
            TransportCompany company("Логистик");
            Route r1("R-1", "А", "Б", 100.0, 1000.0);
            RoadTransport t1("T-1", "КАМАЗ", 20.0, 80.0, 5.0, 4, 500.0);
            Client c1("C-1", "Клиент", false, 0.0);

            company.AddRoute(&r1);
            company.AddTransport(&t1);
            company.AddClient(&c1);

            Assert::IsTrue(&r1 == company.FindRouteById("R-1"));
            Assert::IsNull(company.FindRouteById("NO-ROUTE"));
            Assert::IsTrue(&t1 == company.FindTransportById("T-1"));
            Assert::IsNull(company.FindTransportById("NO-TR"));
            Assert::IsTrue(&c1 == company.FindClientById("C-1"));
            Assert::IsNull(company.FindClientById("NO-CL"));

            Assert::AreEqual(static_cast<size_t>(1), company.GetRoutes().size());
            Assert::AreEqual(static_cast<size_t>(1), company.GetTransports().size());
            Assert::AreEqual(static_cast<size_t>(1), company.GetClients().size());

            // Исключения на nullptr и дубликаты ID
            Assert::ExpectException<std::invalid_argument>([&]() { company.AddRoute(nullptr); });
            Assert::ExpectException<std::invalid_argument>([&]() { company.AddRoute(&r1); });
            Assert::ExpectException<std::invalid_argument>([&]() { company.AddTransport(nullptr); });
            Assert::ExpectException<std::invalid_argument>([&]() { company.AddTransport(&t1); });
            Assert::ExpectException<std::invalid_argument>([&]() { company.AddClient(nullptr); });
            Assert::ExpectException<std::invalid_argument>([&]() { company.AddClient(&c1); });
        }

        /**
         * @brief Проверка AssignTransportToRoute: автодобавление в парк и отсутствие дублей на маршруте
         */
        TEST_METHOD(AssignTransportToRoute_AutoRegisterAndNoDuplicates_Success)
        {
            TransportCompany company("Логистик");
            Route r1("R-1", "А", "Б", 100.0, 1000.0);
            AirTransport air("AIR-1", "Ан-124", 120.0, 800.0, 15.0, 11000.0, 5000.0);

            company.AddRoute(&r1);

            // Назначаем без предварительного AddTransport — должен добавиться в общий список автоматически
            company.AssignTransportToRoute("R-1", &air);
            company.AssignTransportToRoute("R-1", &air); // повторное назначение не создает дубликат

            Assert::AreEqual(static_cast<size_t>(1), company.GetTransports().size());
            Assert::AreEqual(static_cast<size_t>(1), company.GetTransportsByRoute("R-1").size());

            Assert::ExpectException<std::invalid_argument>([&]() { company.AssignTransportToRoute("R-1", nullptr); });
            Assert::ExpectException<std::invalid_argument>([&]() { company.AssignTransportToRoute("UNKNOWN", &air); });
        }

        /**
         * @brief Задание 1: Список маршрутов и цены на них (пустая и заполненная компания)
         */
        TEST_METHOD(Task1_GetRoutesWithPrices_AndReport_Success)
        {
            TransportCompany company("Северная Логистика");

            // Пустая компания
            Assert::IsTrue(company.GetRoutesWithPrices().empty());
            Assert::AreEqual(std::string("Компания не обслуживает маршруты."), company.GetRoutesWithPricesReport());

            // С маршрутами
            Route r1("R-1", "Москва", "Санкт-Петербург", 700.0, 3500.0);
            Route r2("R-2", "Москва", "Казань", 820.0, 4200.0);
            company.AddRoute(&r1);
            company.AddRoute(&r2);

            const auto routesWithPrices = company.GetRoutesWithPrices();
            Assert::AreEqual(static_cast<size_t>(2), routesWithPrices.size());
            Assert::AreEqual(std::string("[R-1] Москва -> Санкт-Петербург"), routesWithPrices[0].first);
            Assert::AreEqual(3500.0, routesWithPrices[0].second, kTolerance);
            Assert::AreEqual(std::string("[R-2] Москва -> Казань"), routesWithPrices[1].first);
            Assert::AreEqual(4200.0, routesWithPrices[1].second, kTolerance);

            const std::string report = company.GetRoutesWithPricesReport();
            Assert::IsTrue(report.find("Москва -> Санкт-Петербург") != std::string::npos);
            Assert::IsTrue(report.find("3500.00") != std::string::npos);
            Assert::IsTrue(report.find("4200.00") != std::string::npos);
        }

        /**
         * @brief Задание 2: Список транспорта на данном маршруте (пустой, заполненный, неизвестный)
         */
        TEST_METHOD(Task2_GetTransportsByRoute_AndReport_Success)
        {
            TransportCompany company("Логистик");
            Route r1("R-1", "Москва", "Тверь", 180.0, 1000.0);
            Route rEmpty("R-2", "Тверь", "Псков", 500.0, 2000.0);
            RoadTransport truck("ROAD-1", "КАМАЗ", 20.0, 85.0, 5.0, 4, 1000.0);
            RailTransport train("RAIL-1", "ВЛ80", 3000.0, 70.0, 3.0, 50, 2000.0);

            company.AddRoute(&r1);
            company.AddRoute(&rEmpty);
            company.AssignTransportToRoute("R-1", &truck);
            company.AssignTransportToRoute("R-1", &train);

            const auto list1 = company.GetTransportsByRoute("R-1");
            Assert::AreEqual(static_cast<size_t>(2), list1.size());
            Assert::AreEqual(std::string("ROAD-1"), list1[0]->GetId());
            Assert::AreEqual(std::string("RAIL-1"), list1[1]->GetId());

            Assert::IsTrue(company.GetTransportsByRoute("R-2").empty());
            Assert::IsTrue(company.GetTransportsByRouteReport("R-2").find("нет назначенного транспорта") != std::string::npos);
            Assert::IsTrue(company.GetTransportsByRouteReport("R-1").find("КАМАЗ") != std::string::npos);

            Assert::ExpectException<std::invalid_argument>([&]() { company.GetTransportsByRoute("NO-ROUTE"); });
            Assert::ExpectException<std::invalid_argument>([&]() { company.GetTransportsByRouteReport("NO-ROUTE"); });
        }

        /**
         * @brief Задание 3: Варианты проезда по маршруту (все 5 видов, дедупликация, пустой маршрут)
         */
        TEST_METHOD(Task3_GetDeliveryOptionsByRoute_AllTypesAndDeduplication_Success)
        {
            TransportCompany company("Мультимодал");
            Route rAll("R-ALL", "Порт А", "Порт Б", 1000.0, 5000.0);
            Route rEmpty("R-EMPTY", "Точка 1", "Точка 2", 100.0, 500.0);

            AirTransport air("AIR-1", "Ан-124", 120.0, 800.0, 15.0, 11000.0, 5000.0);
            RiverTransport river("RIV-1", "Волго-Дон", 5000.0, 20.0, 2.0, 3.5, 1200.0);
            SeaTransport sea1("SEA-1", "Балтика-1", 20000.0, 35.0, 1.5, 1500, 8000.0);
            SeaTransport sea2("SEA-2", "Балтика-2", 18000.0, 32.0, 1.4, 1200, 7000.0);
            RailTransport rail("RAIL-1", "ВЛ80", 3000.0, 70.0, 3.0, 50, 2500.0);
            RoadTransport road("ROAD-1", "КАМАЗ", 20.0, 85.0, 5.0, 4, 1500.0);

            company.AddRoute(&rAll);
            company.AddRoute(&rEmpty);
            company.AssignTransportToRoute("R-ALL", &sea1);
            company.AssignTransportToRoute("R-ALL", &sea2); // дублирующийся тип "Морской"
            company.AssignTransportToRoute("R-ALL", &air);
            company.AssignTransportToRoute("R-ALL", &river);
            company.AssignTransportToRoute("R-ALL", &rail);
            company.AssignTransportToRoute("R-ALL", &road);

            const auto options = company.GetDeliveryOptionsByRoute("R-ALL");
            Assert::AreEqual(static_cast<size_t>(5), options.size());
            Assert::AreEqual(std::string("Автомобильный"), options[0]);
            Assert::AreEqual(std::string("Воздушный"), options[1]);
            Assert::AreEqual(std::string("Железнодорожный"), options[2]);
            Assert::AreEqual(std::string("Морской"), options[3]);
            Assert::AreEqual(std::string("Речной"), options[4]);

            Assert::IsTrue(company.GetDeliveryOptionsByRoute("R-EMPTY").empty());
            Assert::IsTrue(company.GetDeliveryOptionsByRouteReport("R-EMPTY").find("нет доступных вариантов") != std::string::npos);
            Assert::IsTrue(company.GetDeliveryOptionsByRouteReport("R-ALL").find("Морской") != std::string::npos);

            Assert::ExpectException<std::invalid_argument>([&]() { company.GetDeliveryOptionsByRoute("BAD"); });
            Assert::ExpectException<std::invalid_argument>([&]() { company.GetDeliveryOptionsByRouteReport("BAD"); });
        }

        /**
         * @brief Задание 4: Расчет стоимости перевозки по всем 5 видам транспорта и с учетом скидки
         */
        TEST_METHOD(Task4_CalculateCargoDeliveryCost_AllTransportTypesAndDiscount_Success)
        {
            TransportCompany company("Тариф");
            Route route("R-1", "А", "Б", 100.0, 1000.0);
            Client ordinary("C-1", "Обычный", false, 20.0);
            Client regular("C-2", "Постоянный", true, 20.0);

            AirTransport air("AIR-1", "Ан", 100.0, 800.0, 10.0, 10000.0, 500.0);       // 1000 + (100*10*10 + 500) = 11500
            RiverTransport river("RIV-1", "Баржа", 100.0, 20.0, 2.0, 3.0, 200.0);     // 1000 + (100*10*2 + 200)  = 3200
            SeaTransport sea("SEA-1", "Судно", 100.0, 30.0, 1.5, 500, 300.0);         // 1000 + (100*10*1.5 + 300)= 2800
            RailTransport rail("RAIL-1", "Поезд", 100.0, 70.0, 3.0, 20, 400.0);       // 1000 + (100*10*3 + 400)  = 4400
            RoadTransport road("ROAD-1", "Фура", 20.0, 80.0, 5.0, 4, 100.0);          // 1000 + (100*10*5 + 100)  = 6100

            company.AddRoute(&route);
            company.AssignTransportToRoute("R-1", &air);
            company.AssignTransportToRoute("R-1", &river);
            company.AssignTransportToRoute("R-1", &sea);
            company.AssignTransportToRoute("R-1", &rail);
            company.AssignTransportToRoute("R-1", &road);

            Assert::AreEqual(11500.0, company.CalculateCargoDeliveryCost("R-1", &air, &ordinary, 10.0), kTolerance);
            Assert::AreEqual(9200.0, company.CalculateCargoDeliveryCost("R-1", &air, &regular, 10.0), kTolerance);

            Assert::AreEqual(3200.0, company.CalculateCargoDeliveryCost("R-1", &river, &ordinary, 10.0), kTolerance);
            Assert::AreEqual(2560.0, company.CalculateCargoDeliveryCost("R-1", &river, &regular, 10.0), kTolerance);

            Assert::AreEqual(2800.0, company.CalculateCargoDeliveryCost("R-1", &sea, &ordinary, 10.0), kTolerance);
            Assert::AreEqual(2240.0, company.CalculateCargoDeliveryCost("R-1", &sea, &regular, 10.0), kTolerance);

            Assert::AreEqual(4400.0, company.CalculateCargoDeliveryCost("R-1", &rail, &ordinary, 10.0), kTolerance);
            Assert::AreEqual(3520.0, company.CalculateCargoDeliveryCost("R-1", &rail, &regular, 10.0), kTolerance);

            Assert::AreEqual(6100.0, company.CalculateCargoDeliveryCost("R-1", &road, &ordinary, 10.0), kTolerance);
            Assert::AreEqual(4880.0, company.CalculateCargoDeliveryCost("R-1", &road, &regular, 10.0), kTolerance);
        }

        /**
         * @brief Задание 4: Проверка расчета стоимости зарегистрированного заказа CalculateOrderCost
         */
        TEST_METHOD(Task4_CalculateOrderCost_FoundAndNotFound_Success)
        {
            TransportCompany company("Логистик");
            Route route("R-1", "Москва", "Санкт-Петербург", 700.0, 3500.0);
            RoadTransport truck("ROAD-1", "КАМАЗ", 20.0, 85.0, 5.0, 4, 1500.0);
            Client regular("C-1", "Постоянный", true, 10.0);

            company.AddRoute(&route);
            company.AssignTransportToRoute("R-1", &truck);
            company.RegisterOrder(CargoOrder(42, &regular, &route, &truck, "Оборудование", 10.0));

            // rawCost = 3500 + (700*10*5 + 1500) = 40000; со скидкой 10% = 36000
            Assert::AreEqual(36000.0, company.CalculateOrderCost(42), kTolerance);

            Assert::ExpectException<std::invalid_argument>([&]() {
                company.CalculateOrderCost(999);
                });
        }

        /**
         * @brief Задание 5: Грузооборот и масса перевезенных грузов по маршруту (без заказов и с заказами)
         */
        TEST_METHOD(Task5_RouteFreightTurnover_AndReport_Success)
        {
            TransportCompany company("ГрузПоток");
            Route r1("R-1", "Москва", "Санкт-Петербург", 700.0, 3500.0);
            Route r2("R-2", "Москва", "Казань", 800.0, 4000.0);
            Route r3("R-3", "Москва", "Тверь", 180.0, 1000.0);
            RoadTransport truck("ROAD-1", "КАМАЗ", 20.0, 85.0, 5.0, 4, 1500.0);
            Client client("C-1", "ООО Груз", true, 10.0);

            company.AddRoute(&r1);
            company.AddRoute(&r2);
            company.AddRoute(&r3);
            company.AssignTransportToRoute("R-1", &truck);
            company.AssignTransportToRoute("R-2", &truck);

            company.RegisterOrder(CargoOrder(1, &client, &r1, &truck, "Партия 1", 10.0));
            company.RegisterOrder(CargoOrder(2, &client, &r1, &truck, "Партия 2", 15.0));
            company.RegisterOrder(CargoOrder(3, &client, &r2, &truck, "Партия 3", 5.0));

            Assert::AreEqual(static_cast<size_t>(3), company.GetOrders().size());
            Assert::AreEqual(17500.0, company.GetRouteFreightTurnover("R-1"), kTolerance);
            Assert::AreEqual(25.0, company.GetRouteTotalCargoWeight("R-1"), kTolerance);

            Assert::AreEqual(4000.0, company.GetRouteFreightTurnover("R-2"), kTolerance);
            Assert::AreEqual(5.0, company.GetRouteTotalCargoWeight("R-2"), kTolerance);

            // Маршрут без заказов
            Assert::AreEqual(0.0, company.GetRouteFreightTurnover("R-3"), kTolerance);
            Assert::AreEqual(0.0, company.GetRouteTotalCargoWeight("R-3"), kTolerance);

            const std::string report = company.GetRouteFreightTurnoverReport("R-1");
            Assert::IsTrue(report.find("17500.00") != std::string::npos);
            Assert::IsTrue(report.find("25.00") != std::string::npos);

            Assert::ExpectException<std::invalid_argument>([&]() { company.GetRouteFreightTurnover("BAD"); });
            Assert::ExpectException<std::invalid_argument>([&]() { company.GetRouteTotalCargoWeight("BAD"); });
            Assert::ExpectException<std::invalid_argument>([&]() { company.GetRouteFreightTurnoverReport("BAD"); });
        }

        /**
         * @brief Проверка всех исключений RegisterOrder
         */
        TEST_METHOD(RegisterOrder_InvalidConditions_Throws)
        {
            TransportCompany company("Логистик");
            Route rRegistered("R-1", "Москва", "Тверь", 180.0, 1000.0);
            Route rUnregistered("R-2", "Тверь", "Псков", 500.0, 2000.0);
            RoadTransport tAssigned("T-1", "КАМАЗ-1", 20.0, 85.0, 5.0, 4, 500.0);
            RoadTransport tUnassigned("T-2", "КАМАЗ-2", 20.0, 85.0, 5.0, 4, 500.0);
            Client client("C-1", "Клиент", false, 0.0);

            company.AddRoute(&rRegistered);
            company.AssignTransportToRoute("R-1", &tAssigned);
            company.AddTransport(&tUnassigned);

            // 1. Пустой заказ (default-constructed)
            Assert::ExpectException<std::invalid_argument>([&]() {
                company.RegisterOrder(CargoOrder());
                });

            // 2. Маршрут не обслуживается компанией
            Assert::ExpectException<std::invalid_argument>([&]() {
                company.RegisterOrder(CargoOrder(1, &client, &rUnregistered, &tAssigned, "Груз", 5.0));
                });

            // 3. Транспорт не назначен на этот маршрут
            Assert::ExpectException<std::invalid_argument>([&]() {
                company.RegisterOrder(CargoOrder(2, &client, &rRegistered, &tUnassigned, "Груз", 5.0));
                });

            // 4. Дубликат ID заказа
            company.RegisterOrder(CargoOrder(10, &client, &rRegistered, &tAssigned, "Груз 1", 5.0));
            Assert::ExpectException<std::invalid_argument>([&]() {
                company.RegisterOrder(CargoOrder(10, &client, &rRegistered, &tAssigned, "Груз 2", 3.0));
                });
        }

        /**
         * @brief Проверка всех исключений CalculateCargoDeliveryCost
         */
        TEST_METHOD(CalculateCargoDeliveryCost_InvalidConditions_Throws)
        {
            TransportCompany company("Логистик");
            Route r1("R-1", "Москва", "Тверь", 180.0, 1000.0);
            RoadTransport tAssigned("T-1", "КАМАЗ-1", 20.0, 85.0, 5.0, 4, 500.0);
            RoadTransport tUnassigned("T-2", "КАМАЗ-2", 20.0, 85.0, 5.0, 4, 500.0);
            Client client("C-1", "Клиент", false, 0.0);

            company.AddRoute(&r1);
            company.AssignTransportToRoute("R-1", &tAssigned);

            Assert::ExpectException<std::invalid_argument>([&]() {
                company.CalculateCargoDeliveryCost("UNKNOWN", &tAssigned, &client, 5.0);
                });
            Assert::ExpectException<std::invalid_argument>([&]() {
                company.CalculateCargoDeliveryCost("R-1", nullptr, &client, 5.0);
                });
            Assert::ExpectException<std::invalid_argument>([&]() {
                company.CalculateCargoDeliveryCost("R-1", &tAssigned, nullptr, 5.0);
                });
            Assert::ExpectException<std::invalid_argument>([&]() {
                company.CalculateCargoDeliveryCost("R-1", &tUnassigned, &client, 5.0);
                });
            Assert::ExpectException<std::invalid_argument>([&]() {
                company.CalculateCargoDeliveryCost("R-1", &tAssigned, &client, 25.0); // превышение грузоподъемности
                });
        }
    };
}
